import numpy as np

Opt_h_ann = np.array([[ 5.],[17.],[ 5.],[21.],[29.],[25.],[15.],[27.],[23.],[ 1.]])
Error_test_ann = np.array([[80076.13856696],[57040.38971045],[33812.73106403],[46032.87612616],[25172.9912224 ],[51945.71776051],[52019.94072333],[37818.44568168],[66036.04789608],[60697.01915234]])
# Lin reg results
Opt_lambdas_lin = np.array([[ 1.],[10.],[10.],[10.],[10.],[10.],[10.],[10.],[ 1.],[10.]])
Error_test_lin = np.array([[81855.88195553],[58139.61929572],[34477.1682321 ],[47044.39984946],[26923.95029055],[53591.76717343],[53809.68158515],[39397.91949323],[68603.58124102],[61014.41051654]])
# Baseline test
Error_test_baseline = np.array([[87051.66076474],[60814.02445247],[37637.05816853],[51440.01135878],[31167.69666682],[58451.09639776],[59007.37354837],[46516.92024606],[75908.64311779],[69229.67371922]])


# Latex table
for index,res in enumerate(zip(Opt_h_ann, Error_test_ann, Opt_lambdas_lin, Error_test_lin, Error_test_baseline)):
    print(str(index)+" & {0:.3f} & {1:.3f} & {2:.3f} & {3:.3f} & {4:.3f}".format(*[i[0] for i in res])+r" \\")