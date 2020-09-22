%% Note: This piece of code requires you to have imported the data using Matlabs "Import Data" funtion or some
%% other way and that the variables are called XOM etc

%% Exercise 2 %%

% My data is saved in a file called DataWeek36, so I load it here
load('DataWeek36.mat')

% Plot
plot(XOM.Date,XOM.Close);
hold on
plot(XOM.Date,XOM.AdjClose);
close

% Calculate returns
WeeklyReturns = (XOM.AdjClose(2:end)-XOM.AdjClose(1:end-1))./XOM.AdjClose(1:end-1);
plot(XOM.Date(2:end),WeeklyReturns);
close

% Calculate average (by formula, by build-in function, and aritmetric mean)
AverageReturn1 = prod(1+WeeklyReturns)^(1/size(WeeklyReturns,1))-1;
AverageReturn2 = geomean(1+WeeklyReturns)-1;
AverageReturn3 = mean(WeeklyReturns);

% Calculate standard deviation
StdReturns = std(WeeklyReturns);

% Calculate logreturns
WeeklyLogReturns = log(XOM.AdjClose(2:end)) - log(XOM.AdjClose(1:end-1));
plot(XOM.Date(2:end),WeeklyLogReturns);
close
plot(XOM.Date(2:end),WeeklyLogReturns-WeeklyReturns);
close

% Calculate log average
AverageLogReturn = mean(WeeklyLogReturns);

%% Exercise 3 %%

% Plot
hold on
plot(SPY.Date,SPY.AdjClose);
plot(EEM.Date,EEM.AdjClose);
plot(XLF.Date,XLF.AdjClose);
% Here it would be a good idea to insert a legend on your graph. Maybe
% scaling all prices to start at 100 would make it easier to compare across
% assets
close

% Calculate returns
SPY_DailyReturns = (SPY.AdjClose(2:end)-SPY.AdjClose(1:end-1))./SPY.AdjClose(1:end-1);
EEM_DailyReturns = (EEM.AdjClose(2:end)-EEM.AdjClose(1:end-1))./EEM.AdjClose(1:end-1);
XLF_DailyReturns = (XLF.AdjClose(2:end)-XLF.AdjClose(1:end-1))./XLF.AdjClose(1:end-1);

% Calculate average (by formula)
SPY_AveRet = prod(1+SPY_DailyReturns)^(1/size(SPY_DailyReturns,1))-1;
EEM_AveRet = prod(1+EEM_DailyReturns)^(1/size(EEM_DailyReturns,1))-1;
XLF_AveRet = prod(1+XLF_DailyReturns)^(1/size(XLF_DailyReturns,1))-1;

% Calculate standard deviation
SPY_StdDev = std(SPY_DailyReturns);
EEM_StdDev = std(EEM_DailyReturns);
XLF_StdDev = std(XLF_DailyReturns);

% Calculate variance-covariance and correlation
VarCov = cov([SPY_DailyReturns EEM_DailyReturns XLF_DailyReturns]);
Corr = corr([SPY_DailyReturns EEM_DailyReturns XLF_DailyReturns]);

% Week 37 Exercises
XOM_AnnualReturns = ((1+AverageReturn1)^52)-1
XOM_AnnualLogReturns = 52 * AverageLogReturn
AnnualDifference = XOM_AnnualReturns - XOM_AnnualLogReturns

EEM_AnnualReturns = ((1+EEM_AveRet)^252)-1
SPY_AnnualReturns = ((1+SPY_AveRet)^252)-1
XLF_AnnualReturns = ((1+XLF_AveRet)^252)-1

EEM_AnnualSTD = sqrt(252)*EEM_StdDev
SPY_AnnualSTD = sqrt(252)*SPY_StdDev
XLF_AnnualSTD = sqrt(252)*XLF_StdDev

CashFlow1 = [1.5 * ones(floor((datenum('2023-11-15')-datenum(date))/365),1); 101.5]
CleanPrice1 = 110.410
DateRatio1 = 1 - (abs(datenum(date)/datenum('2019-11-15'))/365)
DirtyPrice1 = CleanPrice1 + (1.5 * DateRatio1)





