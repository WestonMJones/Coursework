class Pokemon{
private:
    std::map<std::string,std::vector<std::string> > facts_;
public:
    Pokemon(){};
    Pokemon(std::map<std::string,std::vector<std::string> > facts) : facts_(facts){}
    bool SharesEggGroup(Pokemon* p);
    std::string getLabel(){return facts_["label"][0];}
};

class Monster : public Pokemon{
    Monster(std::map<std::string,std::vector<std::string> > facts) : Pokemon(facts){throw 1;}
};