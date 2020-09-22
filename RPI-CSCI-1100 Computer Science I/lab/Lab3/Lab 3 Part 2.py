def calculate_results(country,num_wins,num_losses,num_draw,goals_for,goals_against):
    points = num_wins * 3+num_draw
    goal_adv = goals_for - goals_against
    print(country)
    print("Win:", num_wins, "Lose:", num_losses, "Draw:", num_draw)
    print("Total number of points:", points, "Goal advantage:", goal_adv)    
    return

## Process results for Germany
calculate_results("Germany",2,1,0,7,2)

## Process results for USA
calculate_results("USA",1,1,1,4,4)

## Process results for Argentina
calculate_results("Argentina",3,0,0,6,3)

## Process results for England
calculate_results("England",0,1,2,2,4)