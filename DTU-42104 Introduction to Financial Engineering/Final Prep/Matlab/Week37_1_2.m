%% Note: This piece of code requires you to have imported the data using Matlabs "Import Data" funtion or some
%% other way and that the variables are called XOM etc

%% Exercise 1 %%
clear
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
AverageReturn3 = mean(WeeklyReturns); % note this is the wrong way to do it!
AnnualAverageReturn = (1+AverageReturn1)^52-1;

% Calculate standard deviation
StdReturns = std(WeeklyReturns);
AnnualStdReturns = sqrt(52)*StdReturns;

% Calculate logreturns
WeeklyLogReturns = log(XOM.AdjClose(2:end)) - log(XOM.AdjClose(1:end-1));
plot(XOM.Date(2:end),WeeklyLogReturns);
close
plot(XOM.Date(2:end),WeeklyLogReturns-WeeklyReturns);
close

% Calculate log average
AverageLogReturn = mean(WeeklyLogReturns);
AnnualAverageLogReturn = 52*mean(WeeklyLogReturns);
StdLogReturns = std(WeeklyLogReturns);
AnnualStdReturns = sqrt(52)*StdLogReturns;
%% Exercise 3 %%

% Plot
hold on
plot(SPY.Date,SPY.AdjClose);
plot(EEM.Date,EEM.AdjClose);
plot(XLF.Date,XLF.AdjClose);
% Here it would be a good idea to insert a legend on your graph
close

% Calculate returns
SPY_DailyReturns = (SPY.AdjClose(2:end)-SPY.AdjClose(1:end-1))./SPY.AdjClose(1:end-1);
EEM_DailyReturns = (EEM.AdjClose(2:end)-EEM.AdjClose(1:end-1))./EEM.AdjClose(1:end-1);
XLF_DailyReturns = (XLF.AdjClose(2:end)-XLF.AdjClose(1:end-1))./XLF.AdjClose(1:end-1);
SPY_DailyLogReturns =diff(log(SPY.AdjClose));
EEM_DailyLogReturns = diff(log(EEM.AdjClose));
XLF_DailyLogReturns = diff(log(XLF.AdjClose));

% Calculate average (by formula)
SPY_AveRet = prod(1+SPY_DailyReturns)^(1/size(SPY_DailyReturns,1))-1;
EEM_AveRet = prod(1+EEM_DailyReturns)^(1/size(EEM_DailyReturns,1))-1;
XLF_AveRet = prod(1+XLF_DailyReturns)^(1/size(XLF_DailyReturns,1))-1;

SPY_AnnAveRet = (1+SPY_AveRet)^252 - 1;
EEM_AnnAveRet = (1+EEM_AveRet)^252 - 1;
XLF_AnnAveRet = (1+XLF_AveRet)^252 - 1;

% Calculate standard deviation
SPY_StdDev = std(SPY_DailyReturns);
EEM_StdDev = std(EEM_DailyReturns);
XLF_StdDev = std(XLF_DailyReturns);

SPY_AnnStdDev = sqrt(252)*std(SPY_DailyReturns);
EEM_AnnStdDev = sqrt(252)*std(EEM_DailyReturns);
XLF_AnnStdDev = sqrt(252)*std(XLF_DailyReturns);

SPY_AnnLogStdDev = sqrt(252)*std(SPY_DailyLogReturns);
EEM_AnnLogStdDev = sqrt(252)*std(EEM_DailyLogReturns);
XLF_AnnLogStdDev = sqrt(252)*std(XLF_DailyLogReturns);

% Calculate variance-covariance and correlation
VarCov = cov([SPY_DailyReturns EEM_DailyReturns XLF_DailyReturns]);
Corr = corr([SPY_DailyReturns EEM_DailyReturns XLF_DailyReturns]);
VarCovAnn = 252*cov([SPY_DailyReturns EEM_DailyReturns XLF_DailyReturns]);

VarCovLog = cov([SPY_DailyLogReturns EEM_DailyLogReturns XLF_DailyLogReturns]);
CorrLog = corr([SPY_DailyLogReturns EEM_DailyLogReturns XLF_DailyLogReturns]);
VarCovLogAnn = 252*cov([SPY_DailyLogReturns EEM_DailyLogReturns XLF_DailyLogReturns]);

SPY.Returns = NaN*ones(length(SPY.Date),1);
SPY.Returns(2:end) = SPY_DailyReturns;
EEM.Returns = NaN*ones(length(EEM.Date),1);
EEM.Returns(2:end) = EEM_DailyReturns;
XLF.Returns = NaN*ones(length(XLF.Date),1);
XLF.Returns(2:end) = XLF_DailyReturns;

