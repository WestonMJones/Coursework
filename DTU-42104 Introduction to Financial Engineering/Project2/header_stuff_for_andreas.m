% % Specify options for importing data
% opts = delimitedTextImportOptions("NumVariables", 7);
% 
% % Specify range and delimiter
% opts.DataLines = [2, Inf];
% opts.Delimiter = ",";
% 
% % Specify column names and types
% opts.VariableNames = ["Date", "Open", "High", "Low", "Close", "AdjClose", "Volume"];
% opts.VariableTypes = ["datetime", "double", "double", "double", "double", "double", "double"];
% opts = setvaropts(opts, 1, "InputFormat", "yyyy-MM-dd");
% opts.ExtraColumnsRule = "ignore";
% opts.EmptyLineRule = "read";
% 
% % Import the data
% CSCO = readtable("C:\Users\andre\Desktop\Project2\CSCO_old.csv", opts);
% FDX = readtable("C:\Users\andre\Desktop\Project2\FDX_old.csv", opts);
% GOOG = readtable("C:\Users\andre\Desktop\Project2\GOOG_old.csv", opts);
% JPM = readtable("C:\Users\andre\Desktop\Project2\JPM_old.csv", opts);
% KO = readtable("C:\Users\andre\Desktop\Project2\KO_old.csv", opts);
% NEM = readtable("C:\Users\andre\Desktop\Project2\NEM_old.csv", opts);
% PFE = readtable("C:\Users\andre\Desktop\Project2\PFE_old.csv", opts);
% PSX = readtable("C:\Users\andre\Desktop\Project2\PSX_old.csv", opts);

% Calculate daily returns
CSCODailyReturns = (CSCO.AdjClose(2:end)-CSCO.AdjClose(1:end-1))./CSCO.AdjClose(1:end-1);
FDXDailyReturns = (FDX.AdjClose(2:end)-FDX.AdjClose(1:end-1))./FDX.AdjClose(1:end-1);
GOOGDailyReturns = (GOOG.AdjClose(2:end)-GOOG.AdjClose(1:end-1))./GOOG.AdjClose(1:end-1);
JPMDailyReturns = (JPM.AdjClose(2:end)-JPM.AdjClose(1:end-1))./JPM.AdjClose(1:end-1);
KODailyReturns = (KO.AdjClose(2:end)-KO.AdjClose(1:end-1))./KO.AdjClose(1:end-1);
NEMDailyReturns = (NEM.AdjClose(2:end)-NEM.AdjClose(1:end-1))./NEM.AdjClose(1:end-1);
PFEDailyReturns = (PFE.AdjClose(2:end)-PFE.AdjClose(1:end-1))./PFE.AdjClose(1:end-1);
PSXDailyReturns = (PSX.AdjClose(2:end)-PSX.AdjClose(1:end-1))./PSX.AdjClose(1:end-1);

% Calculate average returns
CSCOAverageDailyReturn = prod(1+CSCODailyReturns)^(1/size(CSCODailyReturns,1))-1;
FDXAverageDailyReturn = prod(1+FDXDailyReturns)^(1/size(FDXDailyReturns,1))-1;
GOOGAverageDailyReturn = prod(1+GOOGDailyReturns)^(1/size(GOOGDailyReturns,1))-1;
JPMAverageDailyReturn = prod(1+JPMDailyReturns)^(1/size(JPMDailyReturns,1))-1;
KOAverageDailyReturn = prod(1+KODailyReturns)^(1/size(KODailyReturns,1))-1;
NEMAverageDailyReturn = prod(1+NEMDailyReturns)^(1/size(NEMDailyReturns,1))-1;
PFEAverageDailyReturn = prod(1+PFEDailyReturns)^(1/size(PFEDailyReturns,1))-1;
PSXAverageDailyReturn = prod(1+PSXDailyReturns)^(1/size(PSXDailyReturns,1))-1;

%Annualize returns
CSCOAnnualAverageReturn = (1+CSCOAverageDailyReturn)^252-1;
FDXAnnualAverageReturn = (1+FDXAverageDailyReturn)^252-1;
GOOGAnnualAverageReturn = (1+GOOGAverageDailyReturn)^252-1;
JPMAnnualAverageReturn = (1+JPMAverageDailyReturn)^252-1;
KOAnnualAverageReturn = (1+KOAverageDailyReturn)^252-1;
NEMAnnualAverageReturn = (1+NEMAverageDailyReturn)^252-1;
PFEAnnualAverageReturn = (1+PFEAverageDailyReturn)^252-1;
PSXAnnualAverageReturn = (1+PSXAverageDailyReturn)^252-1;

%Standard deviation of returns
CSCOStdReturns = std(CSCODailyReturns);
CSCOAnnualStdReturns = sqrt(252)*CSCOStdReturns;

FDXStdReturns = std(FDXDailyReturns);
FDXAnnualStdReturns = sqrt(252)*FDXStdReturns;

GOOGStdReturns = std(GOOGDailyReturns);
GOOGAnnualStdReturns = sqrt(252)*GOOGStdReturns;

JPMStdReturns = std(JPMDailyReturns);
JPMAnnualStdReturns = sqrt(252)*JPMStdReturns;

KOStdReturns = std(KODailyReturns);
KOAnnualStdReturns = sqrt(252)*KOStdReturns;

NEMStdReturns = std(NEMDailyReturns);
NEMAnnualStdReturns = sqrt(252)*NEMStdReturns;

PFEStdReturns = std(PFEDailyReturns);
PFEAnnualStdReturns = sqrt(252)*PFEStdReturns;

PSXStdReturns = std(PSXDailyReturns);
PSXAnnualStdReturns = sqrt(252)*PSXStdReturns;

%Range of tickers [min, max] in time period
CSCO_range = [min(CSCO.AdjClose),max(CSCO.AdjClose)];
FDX_range = [min(FDX.AdjClose),max(FDX.AdjClose)];
GOOG_range = [min(GOOG.AdjClose),max(GOOG.AdjClose)];
JPM_range = [min(JPM.AdjClose),max(JPM.AdjClose)];
KO_range = [min(KO.AdjClose),max(KO.AdjClose)];
NEM_range = [min(NEM.AdjClose),max(NEM.AdjClose)];
PFE_range = [min(PFE.AdjClose),max(PFE.AdjClose)];
PSX_range = [min(PSX.AdjClose),max(PSX.AdjClose)];

% Skewness and Kurtosis of the returns
CSCO_kur =  kurtosis(CSCODailyReturns);
CSCO_skew = skewness(CSCODailyReturns);
FDX_kur =  kurtosis(FDXDailyReturns);
FDX_skew = skewness(FDXDailyReturns);
GOOG_kur =  kurtosis(GOOGDailyReturns);
GOOG_skew = skewness(GOOGDailyReturns);
JPM_kur =  kurtosis(JPMDailyReturns);
JPM_skew = skewness(JPMDailyReturns);
KO_kur =  kurtosis(KODailyReturns);
KO_skew = skewness(KODailyReturns);
NEM_kur =  kurtosis(NEMDailyReturns);
NEM_skew = skewness(NEMDailyReturns);
PFE_kur =  kurtosis(PFEDailyReturns);
PFE_skew = skewness(PFEDailyReturns);
PSX_kur =  kurtosis(PSXDailyReturns);
PSX_skew = skewness(PSXDailyReturns);

%Autocorrelation of returns
lag = 1;
CSCO_autocorr = acf(CSCODailyReturns,lag);
FDX_autocorr = acf(FDXDailyReturns,lag);
GOOG_autocorr = acf(GOOGDailyReturns,lag);
JPM_autocorr = acf(JPMDailyReturns,lag);
KO_autocorr = acf(KODailyReturns,lag);
NEM_autocorr = acf(NEMDailyReturns,lag);
PFE_autocorr = acf(PFEDailyReturns,lag);
PSX_autocorr = acf(PSXDailyReturns,lag);

%Sharpe Ratio
RFR = 0.02;
CSCO_sharp = (CSCOAnnualAverageReturn-RFR)/CSCOAnnualStdReturns
FDX_sharp = (FDXAnnualAverageReturn-RFR)/FDXAnnualStdReturns
GOOG_sharp = (GOOGAnnualAverageReturn-RFR)/GOOGAnnualStdReturns
JPM_sharp = (JPMAnnualAverageReturn-RFR)/JPMAnnualStdReturns
KO_sharp = (KOAnnualAverageReturn-RFR)/KOAnnualStdReturns
NEM_sharp = (NEMAnnualAverageReturn-RFR)/NEMAnnualStdReturns
PFE_sharp = (PFEAnnualAverageReturn-RFR)/PFEAnnualStdReturns
PSX_sharp = (PSXAnnualAverageReturn-RFR)/PSXAnnualStdReturns




