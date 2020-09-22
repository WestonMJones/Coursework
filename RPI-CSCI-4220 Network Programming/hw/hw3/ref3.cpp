#include "CRI_Serv.h"

CRIServer::CRIServer(string passwd, int port){
    this->password = passwd;
    this->port = port;
}

void CRIServer::StartServer(){
    this->sockfd = socket(AF_INET,SOCK_STREAM,0);
    bzero(&(this->serverAddr),sizeof(this->serverAddr));
    int optval = 1;
    setsockopt(this->sockfd, SOL_SOCKET, SO_REUSEADDR, (const void *)&optval , sizeof(int));
    this->serverAddr.sin_family = AF_INET;
    this->serverAddr.sin_addr.s_addr=htonl(INADDR_ANY);
    this->serverAddr.sin_port=htons(this->port);

    int rc = bind(this->sockfd,(struct sockaddr*)&(this->serverAddr),sizeof(this->serverAddr));
    listen(this->sockfd, SOMAXCONN);
    socklen_t serverAddrLen = sizeof(serverAddr);
    getsockname(sockfd,(struct sockaddr*) &(this->serverAddr),&serverAddrLen);
    cout<<ntohs(serverAddr.sin_port)<<"\n";
    this->HandleConnections();
}

void CRIServer::EndServer(){
    shutdown(this->sockfd, SHUT_RD);
    exit(0);
}

void CRIServer::HandleConnections(){
    while(true){
        FD_ZERO(&(this->readfds));
        FD_SET(this->sockfd, &(this->readfds));
        this->maxfd = this->sockfd;

        //go through FDs and add to the fdset TODO:
        for(int i=0; i<this->sockfds.size(); i++){
            if(sockfds[i] > 0){ //if this is a valid FD, add it to the read set
                FD_SET(sockfds[i], &readfds);
            }
            if(sockfds[i] > this->maxfd){ // if there is a new maximum FD remove old
                this->maxfd = sockfds[i];
            }
        }

        int selectflag = select(this->maxfd+1, &(this->readfds), NULL, NULL, NULL);
        if(selectflag < 0 && errno!=EINTR){
            cout<<"There was an error in SELECT\n";
        }

        if(FD_ISSET(this->sockfd,&readfds)){
            socklen_t clientAddrSize = sizeof(this->clientAddr);
            int newfds = accept(this->sockfd, (struct sockaddr*) &(this->clientAddr), &clientAddrSize);
            if(newfds<0){
                cout<<"Error: Accept\n";
            }

            cout<<"Client "<<inet_ntoa(clientAddr.sin_addr)<<" has connected\n";
            
            //add client to user map
            sockfds.push_back(newfds);
            CRIUser newuser = CRIUser(newfds,false,0);
            this->usermap.insert(make_pair(newfds, newuser));
            string bef = "you have connected\n";
            send(newfds,bef.c_str(),sizeof(char)*bef.length(),0);
        }

        for(int i=0; i<this->sockfds.size(); i++){
            if(FD_ISSET(sockfds[i],&readfds)){
                this->ReadData(sockfds[i]);
            }
        }

        //go through all client sockets and see if there is something to read
    }
}

void CRIServer::ReadData(int fds){
    string recv;
    char buf[1024];
    bzero(buf,sizeof(buf));
    int recvsize = read(fds,buf,1024);
    if(recvsize <= 0){
        //A message size of zero is the client exiting
        RemoveUser(fds); //close the file descriptor
        return;
    }
    recv = string(buf);
    //int parse = recv.find(' ');
    vector<string> userinputvec = ParseInput(recv);
    int argsize = userinputvec.size()-1;
    string command = userinputvec[0];

    if(usermap.at(fds).GetUserName() == "" && command != "USER"){
        //the user did not do USER, should be disconnected
        cout<<"User FDS: "<<fds<<" is being removed because of USER cmd\n";
        string toSend = "First Command must be USER <username>\n";
        send(fds,toSend.c_str(),sizeof(char)*toSend.length(),0);
        RemoveUser(fds);
        return;

    }
    if(command == "USER"){
        //add all of the data
        if(argsize < 1){
            string tosend = "Invalid command, please identify yourself with USER\n";
            send(fds,tosend.c_str(),sizeof(char)*tosend.length(),0);
        }
        else{
            HandleUSER(fds,userinputvec[1]);
        }
    }
    else if(command == "LIST"){
        HandleList(fds, argsize, userinputvec);
    }
    else if(command == "JOIN"){
        HandleJoin(fds,argsize, userinputvec);
    }
    else if(command == "PART"){
        HandlePart(fds,argsize,userinputvec);
    }
    else if(command == "OPERATOR"){
        HandleOperator(fds,argsize,userinputvec);
    }
    else if(command == "KICK"){
        HandleKick(fds,argsize,userinputvec);
    }
    else if(command == "PRIVMSG"){
        HandlePrivMsg(fds,argsize,userinputvec);
    }
    else if(command == "QUIT"){
        HandleQuit(fds);
    }
    else{
        string msg = "Invalid command.\n";
        send(fds,msg.c_str(),sizeof(char)*msg.length(),0);
    }
}

vector<string> CRIServer::ParseInput(string input){
    vector<string> returnvector;
    string curstring = "";
    for(int i = 0;i<input.size();i++){
        if(input[i] == ' ' || input[i] =='\n'){
            returnvector.push_back(curstring);
            curstring = "";
        }
        else{
            curstring+=input[i];
        }
    }
    return returnvector;
}

void CRIServer::HandleUSER(int fds, string username){
    if(usernamemap.find(username) == usernamemap.end()){
        if(!usermap.at(fds).SetUsername(username)){
            string msg = "Cannot change username once set\n";
            send(fds, msg.c_str(), sizeof(char)*msg.length(), 0);
            return;
        } //setusername
        usernamemap.insert(make_pair(username,fds));
        //cout<<"Username: "<<usermap.at(fds).GetUserName();
        cout<<"Successfully added username ("<<username<<") to fd: "<<fds<<"\n";
        string msg = "Welcome "+username+"\n";
        send(fds, msg.c_str(), sizeof(char)*msg.length(), 0);
    }
    else{
        string msg = "Username "+username+" is already in use";
        send(fds, msg.c_str(), sizeof(char)*msg.length(), 0);
    }
    
}

void CRIServer::HandleList(int fds, int argc, vector<string> args){
    string channelstring = "";

    if(argc < 1 || channelmap.find(args[1]) == channelmap.end()){
        channelstring += "There are currently "+to_string(channelmap.size())+" channels\n";
        for(auto itr = channelmap.begin(); itr != channelmap.end(); itr++){
            channelstring+="* "+itr->first+"\n";
        }
        send(fds, channelstring.c_str(), sizeof(char)*channelstring.length(),0);
        return;
    }
    else{ //return users of channel, TODO:TEST WITH VALID CHANNEL
        set<int> channelusr = channelmap.at(args[1]);
        channelstring += "There are currently "+to_string(channelusr.size())+" users\n"; 
        for(int i: channelusr){
            channelstring +="* "+ usermap.at(i).GetUserName()+"\n"; 
        }
        send(fds, channelstring.c_str(), sizeof(char)*channelstring.length(),0);
        return;
    }
}

void CRIServer::HandleJoin(int fds, int argc, vector<string> args){
    if(argc < 1){
        //no server was specified
        string msg = "Please specify a channel to join\n";
        send(fds,msg.c_str(),sizeof(char)*msg.length(),0);
        return;
    }
    string channel = args[1]; //0 is reserved for command, 1 is first arg
    if(channel[0] != '#'){
        //channel name is not valid
        string msg = "Channel names must start with a #\n";
        send(fds,msg.c_str(),sizeof(char)*msg.length(),0);
        return;
    }
    if(channelmap.find(channel) != channelmap.end()){//channel is already created add user to channel
        //add fds to channel set
        channelmap.at(channel).insert(fds);
        //add channel to user
        usermap.at(fds).AddChannel(channel);
        //send message to all in channel
        for(auto itr = channelmap.at(channel).begin(); itr != channelmap.at(channel).end(); itr++){
            if(*itr!=fds){
                string msg =channel+"> "+ usermap.at(fds).GetUserName()+" Joined the channel\n";
                send(*itr,msg.c_str(),sizeof(char)*msg.length(),0);
            }
        }
        cout<<usermap.at(fds).GetUserName()<<" has joined "<<channel<<"\n";
    }
    else{
        //create new channel
        channelmap.insert(make_pair(channel,set<int>()));
        channelmap.at(channel).insert(fds);
        cout<<usermap.at(fds).GetUserName()<<" has Created new "<<channel<<"\n";
    }
}

void CRIServer::HandlePart(int fds, int argc, vector<string> args){
    if(argc < 1){
        //remove the user from all channels
        for(auto itr = channelmap.begin(); itr != channelmap.end() ; itr++){
            if(itr->second.find(fds) != itr->second.end()){
                //remove user from channel
                itr->second.erase(fds);
                //remove channel from user
                usermap.at(fds).RemoveChannel(itr->first);

                //if channel is empty remove channel
                if(itr->second.size() == 0){
                    channelmap.erase(itr->first);
                }
                else{ //there are people still in channel so we need to leave user left message
                    for(auto useritr = channelmap.at(itr->first).begin(); useritr != channelmap.at(itr->first).end(); useritr++){
                        string msg =itr->first+"> "+ usermap.at(fds).GetUserName()+" has left the channel\n";
                        cout<<msg;
                        send(*useritr,msg.c_str(),sizeof(char)*msg.length(),0);
                    }
                }
            }
        }
        return;
    }

    string channel = args[1];
    if(channel[0] != '#'){
        //channel name is not valid
        string msg = "Channel names must start with a #\n";
        send(fds,msg.c_str(),sizeof(char)*msg.length(),0);
        return;
    }

    if(usermap.at(fds).IsInChannel(channel)){
        channelmap.at(channel).erase(fds);
        usermap.at(fds).RemoveChannel(channel);
        if(channelmap.at(channel).size() == 0){
            channelmap.erase(channel);
        }
        else{ //there are people still in channel so we need to leave user left message
            for(auto useritr = channelmap.at(channel).begin(); useritr != channelmap.at(channel).end(); useritr++){
                string msg = channel+"> "+ usermap.at(fds).GetUserName()+" has left the channel\n";
                send(*useritr,msg.c_str(),sizeof(char)*msg.length(),0);
            }
        }
    }
}

void CRIServer::HandleOperator(int fds, int argc, vector<string> args){
    if(argc < 1){
        return;
    }
    if(args[1] == password){
        usermap.at(fds).SetOperator(true);
        string msg = "OPERATOR status bestowed\n";
        send(fds, msg.c_str(),sizeof(char)*msg.length(),0);
    }
    else{
        string msg = "Invalid OPERATOR command\n";
        send(fds, msg.c_str(),sizeof(char)*msg.length(),0);
    }
}

void CRIServer::HandleKick(int fds, int argc, vector<string> args){
    if(argc < 2){
        string msg = "Usage: KICK <#channel> <username>\n";
        send(fds, msg.c_str(),sizeof(char)*msg.length(),0);
        return;
    }
    if(args[1][0] != '#'){
        string msg = "A valid channel name must be sent\n";
        send(fds, msg.c_str(),sizeof(char)*msg.length(),0);
        return;
    }
    if(usermap.at(fds).IsOperator()){
        if(usernamemap.find(args[2]) == usernamemap.end()){ // if said username exists
            cout<<"OP tried to kick invalid username\n";
            return;
        }
        if(channelmap.find(args[1]) == channelmap.end()){
            cout<<"OP tried to kick from invalid channel\n";
            return;
        }
        int kickfd = usernamemap.at(args[2]);
        //remove user from channels user list
        channelmap.at(args[1]).erase(kickfd);
        //remove channel from users channel list
        usermap.at(kickfd).RemoveChannel(args[1]);

        //send kickee a message telling them
        string msg = "You have been kicked from channel "+args[1]+"\n";
        send(kickfd, msg.c_str(),sizeof(char)*msg.length(),0);

        msg = args[1]+"> "+ usermap.at(kickfd).GetUserName()+" was kicked from the channel\n";
        for(auto itr = channelmap.at(args[1]).begin(); itr != channelmap.at(args[1]).end(); itr++){
            send(*itr, msg.c_str(),sizeof(char)*msg.length(),0);
        }

        if(channelmap.at(args[1]).size() == 0){
            channelmap.erase(args[1]);
        }
    }
    else{
        string msg = "You do not have permission to kick from the channel\n";
        send(fds, msg.c_str(),sizeof(char)*msg.length(),0);
    }
}

void CRIServer::HandlePrivMsg(int fds, int argc, vector<string> args){
    if(argc < 2){
        SendToFd(fds, "Usage: PRIVMSG ( <#channel> | <user> ) <message>\n");
        return;
    }
    string msg = "";
    for(int i = 2; i<args.size(); i++){
        msg += args[i]+" ";
    }
    msg+="\n";

    if(args[1][0] == '#'){ //we are sending to a channel
        if(!SendToChannel(args[1],msg)){
            SendToFd(fds, "Specified channel does not exist\n");
            return;
        }
    }
    else{
        if(!SendToUser(args[1],usermap.at(fds).GetUserName()+">> "+msg)){
            SendToFd(fds, "Specified user does not exist\n");
            return;
        }
        else{ //send succeeded
            SendToFd(fds, "<<"+usermap.at(fds).GetUserName()+" "+msg);
        }
    }
    
}

void CRIServer::HandleQuit(int fds){
    vector<string> v;
    HandlePart(fds, 0, v);
    RemoveUser(fds);
}

bool CRIServer::SendToChannel(string channel, string msg){
    if(channelmap.find(channel) != channelmap.end()){
        msg = channel+"> "+msg;
        for(auto itr = channelmap.at(channel).begin(); itr != channelmap.at(channel).end(); itr++){
            send(*itr, msg.c_str(), sizeof(char)*msg.length(), 0);
        }
        return true;
    }
    return false;
}

bool CRIServer::SendToUser(string username, string msg){
    if(usernamemap.find(username) != usernamemap.end()){
        int sendfd = usernamemap.at(username);
        send(sendfd, msg.c_str(), sizeof(char)*msg.length(), 0);
        return true;
    }
    return false;
}

void CRIServer::SendToFd(int fd, string msg){
    send(fd, msg.c_str(), sizeof(char)*msg.length(), 0);
}
bool CRIServer::SendToServer(string msg){
    for(auto itr = usermap.begin(); itr != usermap.end(); itr++){
        int sendfd = itr->first;
        send(sendfd, msg.c_str(), sizeof(char)*msg.length(), 0);
    }
    return true;
}

void CRIServer::RemoveUser(int fds){
    //remove from fd vector
    int i;
    for(i=0;i<sockfds.size();i++){
        if(sockfds[i] == fds){
            sockfds.erase(sockfds.begin()+i);
            break;
        }
    }
    //remove from usernames
    if(usermap.find(fds) != usermap.end()){ //if the fds exists in the map
        usernamemap.erase(usermap.at(fds).GetUserName());
        //remove from channels
        for(auto itr = channelmap.begin();itr != channelmap.end();itr++){
            itr->second.erase(fds);
        }
    }
    else{
        cerr<<"The file descriptor did not exist in user map\n";
    }
    close(fds); //actually close connection
    //remove from fd map 
    usermap.erase(fds);
    cout<<"User has disconnected\n";
}



int main(int argc, char* argv[]){
    string password = "";
    int port = 0;
    for(int i=1; i<argc;i++){
        string optf = argv[i];
        //cout<<argv[i]<<"\n";
        if(optf.find('=')){
            int delim = optf.find('=');
            string opt = optf.substr(0,delim);
            if(opt == "--opt-pass"){
                password = optf.substr(delim+1,optf.length());
                cout<<"Password is: "<<password<<"\n";
            }
            else if(opt == "--opt-port"){
                port = stoi(optf.substr(delim+1,optf.length()).c_str());
                cout<<"Port is: "<<port<<"\n";
            }
        }
    }

    CRIServer server = CRIServer(password,port);
    server.StartServer();
}