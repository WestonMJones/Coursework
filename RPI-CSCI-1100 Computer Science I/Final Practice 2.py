def count_scores(scores):
    start_range = 0
    end_range = 9
    
    for i in range(10):
        count_list = []
        for score in scores:
            if score>=start_range and score<=end_range:
                count_list.append(score)
        count = len(count_list)
        out_string = "[{},{}] : {}".format(start_range,end_range,count)
        print(out_string)
        
        start_range+=10
        end_range+=10
        if end_range==99:
            end_range=100
    return


def interval(v):
    sort(v)
    for i in range(len(v)-9):
        





#v = [ 12, 90, 100, 52, 56, 76, 92, 83, 39, 77, 73, 70, 80 ]
#count_scores(v)
