%% Import Data
% Specify options for importing data
opts = delimitedTextImportOptions("NumVariables", 7);

% Specify range and delimiter
opts.DataLines = [2, Inf];
opts.Delimiter = ",";

% Specify column names and types
opts.VariableNames = ["Date", "Open", "High", "Low", "Close", "AdjClose", "Volume"];
opts.VariableTypes = ["datetime", "double", "double", "double", "double", "double", "double"];
opts = setvaropts(opts, 1, "InputFormat", "yyyy-MM-dd");
opts.ExtraColumnsRule = "ignore";
opts.EmptyLineRule = "read";

% Import the old data for portfolio derivation
CSCO = readtable(".\Data\CSCO_old.csv", opts);
FDX = readtable(".\Data\FDX_old.csv", opts);
GOOG = readtable(".\Data\GOOG_old.csv", opts);
JPM = readtable(".\Data\JPM_old.csv", opts);
KO = readtable(".\Data\KO_old.csv", opts);
NEM = readtable(".\Data\NEM_old.csv", opts);
PFE = readtable(".\Data\PFE_old.csv", opts);
PSX = readtable(".\Data\PSX_old.csv", opts);

% Import the new data for measuring portfolio performance
CSCO_new = readtable(".\Data\CSCO_new.csv", opts);
FDX_new = readtable(".\Data\FDX_new.csv", opts);
GOOG_new = readtable(".\Data\GOOG_new.csv", opts);
JPM_new = readtable(".\Data\JPM_new.csv", opts);
KO_new = readtable(".\Data\KO_new.csv", opts);
NEM_new = readtable(".\Data\NEM_new.csv", opts);
PFE_new = readtable(".\Data\PFE_new.csv", opts);
PSX_new = readtable(".\Data\PSX_new.csv", opts);

%% Basic Data analysis
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

AverageDailyReturn_all = [CSCOAverageDailyReturn; FDXAverageDailyReturn; GOOGAverageDailyReturn; JPMAverageDailyReturn; KOAverageDailyReturn; NEMAverageDailyReturn; PFEAverageDailyReturn; PSXAverageDailyReturn];

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

% Put it into a matrix
u_all = [CSCOAnnualAverageReturn,FDXAnnualAverageReturn,GOOGAnnualAverageReturn,JPMAnnualAverageReturn,KOAnnualAverageReturn,NEMAnnualAverageReturn,PFEAnnualAverageReturn,PSXAnnualAverageReturn];
std_all = [CSCOAnnualStdReturns, FDXAnnualStdReturns,GOOGAnnualStdReturns,JPMAnnualStdReturns,KOAnnualStdReturns,NEMAnnualStdReturns,PFEAnnualStdReturns,PSXAnnualStdReturns];

%% Plotting returns

% Calculate daily compounded return
CSCODailyReturnsCompoundOld = (CSCO.AdjClose(2:5:end)-CSCO.AdjClose(1))./CSCO.AdjClose(1);
FDXDailyReturnsCompoundOld = (FDX.AdjClose(2:5:end)-FDX.AdjClose(1))./FDX.AdjClose(1);
GOOGDailyReturnsCompoundOld = (GOOG.AdjClose(2:5:end)-GOOG.AdjClose(1))./GOOG.AdjClose(1);
JPMDailyReturnsCompoundOld = (JPM.AdjClose(2:5:end)-JPM.AdjClose(1))./JPM.AdjClose(1);
KODailyReturnsCompoundOld = (KO.AdjClose(2:5:end)-KO.AdjClose(1))./KO.AdjClose(1);
NEMDailyReturnsCompoundOld = (NEM.AdjClose(2:5:end)-NEM.AdjClose(1))./NEM.AdjClose(1);
PFEDailyReturnsCompoundOld = (PFE.AdjClose(2:5:end)-PFE.AdjClose(1))./PFE.AdjClose(1);
PSXDailyReturnsCompoundOld = (PSX.AdjClose(2:5:end)-PSX.AdjClose(1))./PSX.AdjClose(1);

% Plot compounded return
figure(1)
days = linspace(0,length(CSCODailyReturnsCompoundOld),length(CSCODailyReturnsCompoundOld));
plot(days,CSCODailyReturnsCompoundOld);
title('Overview of chosen stock returns');
xlabel('Trading weeks since 1st of January 2014 ');
ylabel('Percent Change in value');

hold on;
plot(days,FDXDailyReturnsCompoundOld);
plot(days,GOOGDailyReturnsCompoundOld);
plot(days,JPMDailyReturnsCompoundOld);
plot(days,KODailyReturnsCompoundOld);
plot(days,NEMDailyReturnsCompoundOld);
plot(days,PFEDailyReturnsCompoundOld);
plot(days,PSXDailyReturnsCompoundOld);
legend('CSCO','FDX','GOOG','JPM','KO','NEM','PFE','PSX');
hold off;
close;

%% More Data Analysis

%Correlation between returns
Correlation = corr([CSCODailyReturns FDXDailyReturns GOOGDailyReturns JPMDailyReturns KODailyReturns NEMDailyReturns PFEDailyReturns PSXDailyReturns]);

%Distribution of returns
figure(2);
ksdensity(CSCODailyReturns);
hold on;
CSCOx = [-.1:.001:.1];
CSCOy = normpdf(CSCOx,CSCOAverageDailyReturn,CSCOStdReturns);
plot(CSCOx,CSCOy);
title('Empirical Density of CSCO Returns vs Normal Distribution');
legend({'Empirical','Normal'},'Location','northeast');
hold off;
close;

figure(3);
ksdensity(FDXDailyReturns);
hold on;
FDXx = [-.1:.001:.1];
FDXy = normpdf(FDXx,FDXAverageDailyReturn,FDXStdReturns);
plot(FDXx,FDXy);
title('Empirical Density of FDX Returns vs Normal Distribution');
legend({'Empirical','Normal'},'Location','northeast');
hold off;
close;

figure(4);
ksdensity(GOOGDailyReturns);
hold on;
GOOGx = [-.1:.001:.1];
GOOGy = normpdf(GOOGx,GOOGAverageDailyReturn,GOOGStdReturns);
plot(GOOGx,GOOGy);
title('Empirical Density of GOOG Returns vs Normal Distribution');
legend({'Empirical','Normal'},'Location','northeast');
hold off;
close;

figure(5);
ksdensity(JPMDailyReturns);
hold on;
JPMx = [-.1:.001:.1];
JPMy = normpdf(JPMx,JPMAverageDailyReturn,JPMStdReturns);
plot(JPMx,JPMy);
title('Empirical Density of JPM Returns vs Normal Distribution');
legend({'Empirical','Normal'},'Location','northeast');
hold off;
close;

figure(6);
ksdensity(KODailyReturns);
hold on;
KOx = [-.1:.001:.1];
KOy = normpdf(KOx,KOAverageDailyReturn,KOStdReturns);
plot(KOx,KOy);
title('Empirical Density of KO Returns vs Normal Distribution');
legend({'Empirical','Normal'},'Location','northeast');
hold off;
close;

figure(7);
ksdensity(NEMDailyReturns);
hold on;
NEMx = [-.1:.001:.1];
NEMy = normpdf(NEMx,NEMAverageDailyReturn,NEMStdReturns);
plot(NEMx,NEMy);
title('Empirical Density of NEM Returns vs Normal Distribution');
legend({'Empirical','Normal'},'Location','northeast');
hold off;
close;

figure(8);
ksdensity(PFEDailyReturns);
hold on;
PFEx = [-.1:.001:.1];
PFEy = normpdf(PFEx,PFEAverageDailyReturn,PFEStdReturns);
plot(PFEx,PFEy);
title('Empirical Density of PFE Returns vs Normal Distribution');
legend({'Empirical','Normal'},'Location','northeast');
hold off;
close;

figure(9);
ksdensity(PSXDailyReturns);
hold on;
PSXx = [-.1:.001:.1];
PSXy = normpdf(PSXx,PFEAverageDailyReturn,PSXStdReturns);
plot(PSXx,PSXy);
title('Empirical Density of PSX Returns vs Normal Distribution');
legend({'Empirical','Normal'},'Location','northeast');
hold off;
close;

%Range of tickers [min, max] in time period
CSCO_range = abs(diff([min(CSCODailyReturns),max(CSCODailyReturns)]));
FDX_range = abs(diff([min(FDXDailyReturns),max(FDXDailyReturns)]));
GOOG_range = abs(diff([min(GOOGDailyReturns),max(GOOGDailyReturns)]));
JPM_range = abs(diff([min(JPMDailyReturns),max(JPMDailyReturns)]));
KO_range = abs(diff([min(KODailyReturns),max(KODailyReturns)]));
NEM_range = abs(diff([min(NEMDailyReturns),max(NEMDailyReturns)]));
PFE_range = abs(diff([min(PFEDailyReturns),max(PFEDailyReturns)]));
PSX_range = abs(diff([min(PSXDailyReturns),max(PSXDailyReturns)]));

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
CSCO_sharp = (CSCOAnnualAverageReturn-RFR)/CSCOAnnualStdReturns;
FDX_sharp = (FDXAnnualAverageReturn-RFR)/FDXAnnualStdReturns;
GOOG_sharp = (GOOGAnnualAverageReturn-RFR)/GOOGAnnualStdReturns;
JPM_sharp = (JPMAnnualAverageReturn-RFR)/JPMAnnualStdReturns;
KO_sharp = (KOAnnualAverageReturn-RFR)/KOAnnualStdReturns;
NEM_sharp = (NEMAnnualAverageReturn-RFR)/NEMAnnualStdReturns;
PFE_sharp = (PFEAnnualAverageReturn-RFR)/PFEAnnualStdReturns;
PSX_sharp = (PSXAnnualAverageReturn-RFR)/PSXAnnualStdReturns;

%% Tabulating statisitcs
Stocks = ["CSCO";"FDX";"GOOG";"JPM";"KO";"NEM";"PFE";"PSX"];
Name = ["Cisco Systems"; "FedEx Corporation"; "Alphabet Inc Class A";"JPMorgan Chase & Co."; "Coca-Cola Company";"Newmont Goldcorp";"Pfizer Inc.";"Phillips 66"];
Sector = ["Information Technology";"Industrials";"Communication Services";"Financials";"Consumer Staples";"Materials";"Health Care";"Energy"];

range_all = [CSCO_range;FDX_range;GOOG_range;JPM_range;KO_range;NEM_range;PFE_range;PSX_range];
sharpe_all = [CSCO_sharp;FDX_sharp;GOOG_sharp;JPM_sharp;KO_sharp;NEM_sharp;PFE_sharp;PSX_sharp];
skew_all = [CSCO_skew;FDX_skew;GOOG_skew;JPM_skew;KO_skew;NEM_skew;PFE_skew;PSX_skew];
kur_all = [CSCO_kur;FDX_kur;GOOG_kur;JPM_kur;KO_kur;NEM_kur;PFE_kur;PSX_kur];
autocorr_all = [CSCO_autocorr;FDX_autocorr;GOOG_autocorr;JPM_autocorr;KO_autocorr;NEM_autocorr;PFE_autocorr;PSX_autocorr];

stats_table = table(range_all,skew_all,kur_all,autocorr_all,sharpe_all);
stats_table(1:8,:);

%% Portfolio Derivation

%Calculate Covariance to be used as Sigma
Covar = cov([CSCODailyReturns, FDXDailyReturns, GOOGDailyReturns, JPMDailyReturns, KODailyReturns, NEMDailyReturns, PFEDailyReturns, PSXDailyReturns])*252;

%% Portfolio 1 - Risky-assets only min. variance

mu = u_all';
Sigma = Covar;
a = mu'/Sigma*mu;
b = mu'/Sigma*ones(length(mu),1);
c = ones(length(mu),1)'/Sigma*ones(length(mu),1);
SigmaInv = inv(Sigma);
ParabolaCoeff = [a/(a*c-b^2) -2*b/(a*c-b^2) c/(a*c-b^2)];
w = SigmaInv*[mu ones(length(mu),1)]*[[c -b];[-b a]]/((a*c-b^2));

mu_gmv = b/c;
sigma_gmv = (1/c)^0.5;
w_gmv = (1/c)*SigmaInv*ones(length(mu),1);

Aeq = ones(1,length(mu)); % weights summing to 1
beq = 1;

Aeq(2,:) = (mu'); % expected return

lb = [];
ub = [];

options= optimset('Display','off');
for i=1:101
    ReqMean(i) = (max(mu)-min(mu))/100*(i-1)+min(mu);
    i;
    beq(2,1) = ReqMean(i); % setting the required return equal to the value defined above
    [w_nr(:,i),sigma2_P(i)] = fmincon(@CalcVariance,w_gmv, [],[],Aeq, beq, lb, ub, [], options, Sigma); % minimize the variance subject to constraints
    sigma_P(i) = sqrt(sigma2_P(i));
end

[ind1, ind2] = min(sigma2_P);
sigma_gmv_SS = sigma2_P(ind2).^0.5;
mu_gmv_SS = ReqMean(ind2);
w_gmv_SS = w_nr(:,ind2);

mu_vector = (min(mu) - range(mu)):0.001:(max(mu) + range(mu));
EF_sigma = ((c*mu_vector.^2-2*b*mu_vector + a)/(a*c-b^2)).^(1/2);
figure(10);
plot(EF_sigma,mu_vector);
title('Portfolio 1 - Min Variance Risky Assets Only');
xlabel('Standard Deviation');
ylabel('Mean Return');
hold on;
plot(sigma_P,ReqMean);
hold off;
close;


w_p1 = w_gmv_SS;
u_p1 = dot(w_p1,u_all);
var_p1 = w_p1'*Covar*w_p1;

%% Portfolio 2 - Tangent portfolio

u_riskfree = 0.02;
u_excess = (u_all - u_riskfree)';

u_tan = (u_excess'*inv(Sigma)*u_excess)/(ones(length(u_all),1)'*inv(Sigma)*u_excess);
sd_tan = sqrt(u_excess'*inv(Sigma)*u_excess)/(ones(length(u_all),1)'*inv(Sigma)*u_excess);
w_tan = (inv(Sigma)*u_excess)/(ones(length(u_all),1)'*inv(Sigma)*u_excess);

w_p2 = w_tan;
u_p2 = dot(w_p2,u_all);
var_p2 = w_p2'*Covar*w_p2;

%% Portfolio 3 - Risky-assets only min. variance, no shortselling 

mu = u_all';
Sigma = Covar;
a = mu'/Sigma*mu;
b = mu'/Sigma*ones(length(mu),1);
c = ones(length(mu),1)'/Sigma*ones(length(mu),1);
SigmaInv = inv(Sigma);
ParabolaCoeff = [a/(a*c-b^2) -2*b/(a*c-b^2) c/(a*c-b^2)];
w = SigmaInv*[mu ones(length(mu),1)]*[[c -b];[-b a]]/((a*c-b^2));

mu_gmv = b/c;
sigma_gmv = (1/c)^0.5;
w_gmv = (1/c)*SigmaInv*ones(length(mu),1);

Aeq = ones(1,length(mu)); % weights summing to 1
beq = 1;

Aeq(2,:) = (mu'); % expected return

ub = ones(length(mu),1); %  restrictions
lb = zeros(length(mu),1); % short selling restrictions

options= optimset('Display','off');
for i=1:101
    ReqMean(i) = (max(mu)-min(mu))/100*(i-1)+min(mu);
    i;
    beq(2,1) = ReqMean(i); % setting the required return equal to the value defined above
    [w_nr(:,i),sigma2_P(i)] = fmincon(@CalcVariance,w_gmv, [],[],Aeq, beq, lb, ub, [], options, Sigma); % minimize the variance subject to constraints
    sigma_P(i) = sqrt(sigma2_P(i));
end

[ind1, ind2] = min(sigma2_P);
sigma_gmv_SS = sigma2_P(ind2).^0.5;
mu_gmv_SS = ReqMean(ind2);
w_gmv_SS = w_nr(:,ind2);

mu_vector = (min(mu) - range(mu)):0.001:(max(mu) + range(mu));
EF_sigma = ((c*mu_vector.^2-2*b*mu_vector + a)/(a*c-b^2)).^(1/2);
figure(11);
plot(EF_sigma,mu_vector);
title('Portfolio 3 - Min Variance Risky Assets Only & No SS');
xlabel('Standard Deviation');
ylabel('Mean Return');
hold on;
plot(sigma_P,ReqMean);
hold off;
close;

w_p3 = w_gmv_SS;
u_p3 = dot(w_p3,u_all);
var_p3 = w_p3'*Covar*w_p3;

%% Portfolio 4 - Risky-assets only, max return, no shortselling

w_p4 = zeros(length(u_all),1);
max_ret = find(u_all==max(u_all));
w_p4(max_ret)=1;


u_p4 = dot(w_p4,u_all);
var_p4 = w_p4'*Covar*w_p4;

%% Portfolio 5 - Equal weights

w_p5 = 1/8*ones(8,1);
u_p5 = dot(w_p5,u_all);
var_p5 = w_p5'*Covar*w_p5;

%% Portfolio 6 - Risky-assets only min. variance, max 0.20 for w_i, for i in
%%[1,8]

mu = u_all';
Sigma = Covar;
a = mu'/Sigma*mu;
b = mu'/Sigma*ones(length(mu),1);
c = ones(length(mu),1)'/Sigma*ones(length(mu),1);
SigmaInv = inv(Sigma);
ParabolaCoeff = [a/(a*c-b^2) -2*b/(a*c-b^2) c/(a*c-b^2)];
w = SigmaInv*[mu ones(length(mu),1)]*[[c -b];[-b a]]/((a*c-b^2));

mu_gmv = b/c;
sigma_gmv = (1/c)^0.5;
w_gmv = (1/c)*SigmaInv*ones(length(mu),1);

Aeq = ones(1,length(mu)); % weights summing to 1
beq = 1;

Aeq(2,:) = (mu'); % expected return

ub = ones(length(mu),1)/5; % maximum of 20% in a single asset - restrictions
lb = zeros(length(mu),1); % short selling restrictions

options= optimset('Display','off');
for i=1:101
    ReqMean(i) = (max(mu)-min(mu))/100*(i-1)+min(mu);
    i;
    beq(2,1) = ReqMean(i); % setting the required return equal to the value defined above
    [w_nr(:,i),sigma2_P(i)] = fmincon(@CalcVariance,w_gmv, [],[],Aeq, beq, [], ub, [], options, Sigma); % minimize the variance subject to constraints
    sigma_P(i) = sqrt(sigma2_P(i));
end

[ind1, ind2] = min(sigma2_P);
sigma_gmv_SS = sigma2_P(ind2).^0.5;
mu_gmv_SS = ReqMean(ind2);
w_gmv_SS = w_nr(:,ind2);

mu_vector = (min(mu) - range(mu)):0.001:(max(mu) + range(mu));
EF_sigma = ((c*mu_vector.^2-2*b*mu_vector + a)/(a*c-b^2)).^(1/2);
figure(12);
plot(EF_sigma,mu_vector) 
title('Portfolio 6 - Min Variance Risky Assets Only & No SS & 20% Restriction');
xlabel('Standard Deviation');
ylabel('Mean Return');
hold on
plot(sigma_P,ReqMean)
hold off;
close;

w_p6 = w_gmv_SS;
u_p6 = dot(w_p6,u_all);
var_p6 = w_p6'*Covar*w_p6;

%% Portfolio 7 - Risky-assets only min. variance, min 0.08 for w_i, for i in
%%[1,8]
mu = u_all';
Sigma = Covar;
a = mu'/Sigma*mu;
b = mu'/Sigma*ones(length(mu),1);
c = ones(length(mu),1)'/Sigma*ones(length(mu),1);
SigmaInv = inv(Sigma);
ParabolaCoeff = [a/(a*c-b^2) -2*b/(a*c-b^2) c/(a*c-b^2)];
w = SigmaInv*[mu ones(length(mu),1)]*[[c -b];[-b a]]/((a*c-b^2));

mu_gmv = b/c;
sigma_gmv = (1/c)^0.5;
w_gmv = (1/c)*SigmaInv*ones(length(mu),1);

Aeq = ones(1,length(mu)); % weights summing to 1
beq = 1;

Aeq(2,:) = (mu'); % expected return


ub = ones(length(mu),1); % short selling restrictions
lb = (ones(length(mu),1)*2)/25; % no less than 8% in each asset

options= optimset('Display','off');
for i=1:101
    ReqMean(i) = (max(mu)-min(mu))/100*(i-1)+min(mu);
    i;
    beq(2,1) = ReqMean(i); % setting the required return equal to the value defined above
    [w_nr(:,i),sigma2_P(i)] = fmincon(@CalcVariance,w_gmv, [],[],Aeq, beq, lb, ub, [], options, Sigma); % minimize the variance subject to constraints
    sigma_P(i) = sqrt(sigma2_P(i));
end

[ind1, ind2] = min(sigma2_P);
sigma_gmv_SS = sigma2_P(ind2).^0.5;
mu_gmv_SS = ReqMean(ind2);
w_gmv_SS = w_nr(:,ind2);

mu_vector = (min(mu) - range(mu)):0.001:(max(mu) + range(mu));
EF_sigma = ((c*mu_vector.^2-2*b*mu_vector + a)/(a*c-b^2)).^(1/2);
figure(13);
plot(EF_sigma,mu_vector);

title('Portfolio 7 - Min Variance Risky Assets Only & No SS & 8% Restriction');
xlabel('Standard Deviation');
ylabel('Mean Return');
hold on
plot(sigma_P,ReqMean);
hold off;
close;

w_p7 = w_gmv_SS;
u_p7 = dot(w_p7,u_all);
var_p7 = w_p7'*Covar*w_p7;

%% Table of portfolios

port =   ["p1"; "p2"; "p3"; "p4"; "p5"; "p6"; "p7"];
w_port = [w_p1'; w_p2'; w_p3'; w_p4'; w_p5'; w_p6'; w_p7'];
u_port = [u_p1; u_p2; u_p3; u_p4; u_p5; u_p6; u_p7];
var_port = [var_p1; var_p2; var_p3; var_p4; var_p5; var_p6; var_p7];
label_port = ["", Stocks', "Return", "Standard deviation"]; 
T_port = [label_port; port, w_port, u_port, sqrt(var_port)]';

%% New statistics for chosen stocks

% Calculate new daily returns
CSCODailyReturnsNew = (CSCO_new.AdjClose(2:end)-CSCO_new.AdjClose(1:end-1))./CSCO_new.AdjClose(1:end-1);
FDXDailyReturnsNew = (FDX_new.AdjClose(2:end)-FDX_new.AdjClose(1:end-1))./FDX_new.AdjClose(1:end-1);
GOOGDailyReturnsNew = (GOOG_new.AdjClose(2:end)-GOOG_new.AdjClose(1:end-1))./GOOG_new.AdjClose(1:end-1);
JPMDailyReturnsNew = (JPM_new.AdjClose(2:end)-JPM_new.AdjClose(1:end-1))./JPM_new.AdjClose(1:end-1);
KODailyReturnsNew = (KO_new.AdjClose(2:end)-KO_new.AdjClose(1:end-1))./KO_new.AdjClose(1:end-1);
NEMDailyReturnsNew = (NEM_new.AdjClose(2:end)-NEM_new.AdjClose(1:end-1))./NEM_new.AdjClose(1:end-1);
PFEDailyReturnsNew = (PFE_new.AdjClose(2:end)-PFE_new.AdjClose(1:end-1))./PFE_new.AdjClose(1:end-1);
PSXDailyReturnsNew = (PSX_new.AdjClose(2:end)-PSX_new.AdjClose(1:end-1))./PSX_new.AdjClose(1:end-1);

% Calculate average returns
CSCOAverageDailyReturnNew = prod(1+CSCODailyReturnsNew)^(1/size(CSCODailyReturnsNew,1))-1;
FDXAverageDailyReturnNew = prod(1+FDXDailyReturnsNew)^(1/size(FDXDailyReturnsNew,1))-1;
GOOGAverageDailyReturnNew = prod(1+GOOGDailyReturnsNew)^(1/size(GOOGDailyReturnsNew,1))-1;
JPMAverageDailyReturnNew = prod(1+JPMDailyReturnsNew)^(1/size(JPMDailyReturnsNew,1))-1;
KOAverageDailyReturnNew = prod(1+KODailyReturnsNew)^(1/size(KODailyReturnsNew,1))-1;
NEMAverageDailyReturnNew = prod(1+NEMDailyReturnsNew)^(1/size(NEMDailyReturnsNew,1))-1;
PFEAverageDailyReturnNew = prod(1+PFEDailyReturnsNew)^(1/size(PFEDailyReturnsNew,1))-1;
PSXAverageDailyReturnNew = prod(1+PSXDailyReturnsNew)^(1/size(PSXDailyReturnsNew,1))-1;


% Calculate daily compounded return
CSCODailyReturnsCompoundNew = (CSCO_new.AdjClose(2:end)-CSCO_new.AdjClose(1))./CSCO_new.AdjClose(1);
FDXDailyReturnsCompoundNew = (FDX_new.AdjClose(2:end)-FDX_new.AdjClose(1))./FDX_new.AdjClose(1);
GOOGDailyReturnsCompoundNew = (GOOG_new.AdjClose(2:end)-GOOG_new.AdjClose(1))./GOOG_new.AdjClose(1);
JPMDailyReturnsCompoundNew = (JPM_new.AdjClose(2:end)-JPM_new.AdjClose(1))./JPM_new.AdjClose(1);
KODailyReturnsCompoundNew = (KO_new.AdjClose(2:end)-KO_new.AdjClose(1))./KO_new.AdjClose(1);
NEMDailyReturnsCompoundNew = (NEM_new.AdjClose(2:end)-NEM_new.AdjClose(1))./NEM_new.AdjClose(1);
PFEDailyReturnsCompoundNew = (PFE_new.AdjClose(2:end)-PFE_new.AdjClose(1))./PFE_new.AdjClose(1);
PSXDailyReturnsCompoundNew = (PSX_new.AdjClose(2:end)-PSX_new.AdjClose(1))./PSX_new.AdjClose(1);

ReturnCompound_all = [CSCODailyReturnsCompoundNew';FDXDailyReturnsCompoundNew';GOOGDailyReturnsCompoundNew';JPMDailyReturnsCompoundNew';KODailyReturnsCompoundNew';NEMDailyReturnsCompoundNew';PFEDailyReturnsCompoundNew';PSXDailyReturnsCompoundNew'];

%Annualize returns
CSCOAnnualAverageReturnNew = (1+CSCOAverageDailyReturnNew)^252-1;
FDXAnnualAverageReturnNew = (1+FDXAverageDailyReturnNew)^252-1;
GOOGAnnualAverageReturnNew = (1+GOOGAverageDailyReturnNew)^252-1;
JPMAnnualAverageReturnNew = (1+JPMAverageDailyReturnNew)^252-1;
KOAnnualAverageReturnNew = (1+KOAverageDailyReturnNew)^252-1;
NEMAnnualAverageReturnNew = (1+NEMAverageDailyReturnNew)^252-1;
PFEAnnualAverageReturnNew = (1+PFEAverageDailyReturnNew)^252-1;
PSXAnnualAverageReturnNew = (1+PSXAverageDailyReturnNew)^252-1;

% Standard deviation of returns
CSCOStdReturnsNew = std(CSCODailyReturnsNew);
CSCOAnnualStdReturnsNew = sqrt(252)*CSCOStdReturnsNew;

FDXStdReturnsNew = std(FDXDailyReturnsNew);
FDXAnnualStdReturnsNew = sqrt(252)*FDXStdReturnsNew;

GOOGStdReturnsNew = std(GOOGDailyReturnsNew);
GOOGAnnualStdReturnsNew = sqrt(252)*GOOGStdReturnsNew;

JPMStdReturnsNew = std(JPMDailyReturnsNew);
JPMAnnualStdReturnsNew = sqrt(252)*JPMStdReturnsNew;

KOStdReturnsNew = std(KODailyReturnsNew);
KOAnnualStdReturnsNew = sqrt(252)*KOStdReturnsNew;

NEMStdReturnsNew = std(NEMDailyReturnsNew);
NEMAnnualStdReturnsNew = sqrt(252)*NEMStdReturnsNew;

PFEStdReturnsNew = std(PFEDailyReturnsNew);
PFEAnnualStdReturnsNew = sqrt(252)*PFEStdReturnsNew;

PSXStdReturnsNew = std(PSXDailyReturnsNew);
PSXAnnualStdReturnsNew = sqrt(252)*PSXStdReturnsNew;

%% Analysis of Portfolio Performance
% Relative return of each stock
CSGOrelativeReturn = (CSCO_new.AdjClose(end)-CSCO_new.AdjClose(2))/CSCO_new.AdjClose(2);
FDXrelativeReturn = (FDX_new.AdjClose(end)-FDX_new.AdjClose(2))/FDX_new.AdjClose(2);
GOOGrelativeReturn = (GOOG_new.AdjClose(end)-GOOG_new.AdjClose(2))/GOOG_new.AdjClose(2);
JPMrelativeReturn = (JPM_new.AdjClose(end)-JPM_new.AdjClose(2))/JPM_new.AdjClose(2);
KOrelativeReturn = (KO_new.AdjClose(end)-KO_new.AdjClose(2))/KO_new.AdjClose(2);
NEMrelativeReturn = (NEM_new.AdjClose(end)-NEM_new.AdjClose(2))/NEM_new.AdjClose(2);
PFErelativeReturn = (PFE_new.AdjClose(end)-PFE_new.AdjClose(2))/PFE_new.AdjClose(2);
PSXrelativeReturn = (PSX_new.AdjClose(end)-PSX_new.AdjClose(2))/PSX_new.AdjClose(2);

NewReturn_all = [CSGOrelativeReturn; FDXrelativeReturn; GOOGrelativeReturn; JPMrelativeReturn; KOrelativeReturn; NEMrelativeReturn; PFErelativeReturn; PSXrelativeReturn];

Performance_p1 = dot(w_p1,NewReturn_all);
Performance_p2 = dot(w_p2,NewReturn_all);
Performance_p3 = dot(w_p3,NewReturn_all);
Performance_p4 = dot(w_p4,NewReturn_all);
Performance_p5 = dot(w_p5,NewReturn_all);
Performance_p6 = dot(w_p6,NewReturn_all);
Performance_p7 = dot(w_p7,NewReturn_all);

Performance_all = [Performance_p1; Performance_p2;Performance_p3;Performance_p4;Performance_p5;Performance_p6;Performance_p7];

% Actual variance of portfolios
Covar_actual = cov([CSCODailyReturnsNew, FDXDailyReturnsNew, GOOGDailyReturnsNew, JPMDailyReturnsNew, KODailyReturnsNew, NEMDailyReturnsNew, PFEDailyReturnsNew, PSXDailyReturnsNew])*252;

var_p1_act = w_p1'*Covar_actual*w_p1;
var_p2_act = w_p2'*Covar_actual*w_p2;
var_p3_act = w_p3'*Covar_actual*w_p3;
var_p4_act = w_p4'*Covar_actual*w_p4;
var_p5_act = w_p5'*Covar_actual*w_p5;
var_p6_act = w_p6'*Covar_actual*w_p6;
var_p7_act = w_p7'*Covar_actual*w_p7;
var_port_act = [var_p1_act; var_p2_act; var_p3_act; var_p4_act; var_p5_act; var_p6_act; var_p7_act];

% Relative value of portfolio since 1st of january
relValue_p1 = w_p1'*ReturnCompound_all;
relValue_p2 = w_p2'*ReturnCompound_all;
relValue_p3 = w_p3'*ReturnCompound_all;
relValue_p4 = w_p4'*ReturnCompound_all;
relValue_p5 = w_p5'*ReturnCompound_all;
relValue_p6 = w_p6'*ReturnCompound_all;
relValue_p7 = w_p7'*ReturnCompound_all;

x = linspace(0,length(ReturnCompound_all),length(ReturnCompound_all));
figure(14);
plot(x,relValue_p1)
title('Combine Plots of portfolios')
xlabel('Trading days since 1st of january')
ylabel('Compounded return')

hold on
plot(x,relValue_p2)
plot(x,relValue_p3)
plot(x,relValue_p4)
plot(x,relValue_p5) 
plot(x,relValue_p6)
plot(x,relValue_p7)

legend('p1','p2','p3','p4','p5','p6','p7')
hold off
close;

label_actual = ["", "Return", "Return pred", "RE %", "Standard Deviation", "SD prediction", "RE %"]; 
T_actual = [label_actual;port, Performance_all, u_port, 100*(u_port-Performance_all)./Performance_all, sqrt(var_port_act), sqrt(var_port),100*(sqrt(var_port)-sqrt(var_port_act))./sqrt(var_port_act)];

%% Distribution of returns new data
figure(15);
ksdensity(CSCODailyReturnsNew);
hold on;
CSCOx = [-.1:.001:.1];
CSCOy = normpdf(CSCOx,CSCOAverageDailyReturnNew,CSCOStdReturnsNew);
plot(CSCOx,CSCOy);
title('Empirical Density of CSCO Returns vs Normal Distribution');
legend({'Empirical','Normal'},'Location','northeast');
hold off;
close;

figure(16);
ksdensity(FDXDailyReturns);
hold on;
FDXx = [-.1:.001:.1];
FDXy = normpdf(FDXx,FDXAverageDailyReturn,FDXStdReturns);
plot(FDXx,FDXy);
title('Empirical Density of FDX Returns vs Normal Distribution');
legend({'Empirical','Normal'},'Location','northeast');
hold off;
close;

figure(17);
ksdensity(GOOGDailyReturns);
hold on;
GOOGx = [-.1:.001:.1];
GOOGy = normpdf(GOOGx,GOOGAverageDailyReturn,GOOGStdReturns);
plot(GOOGx,GOOGy);
title('Empirical Density of GOOG Returns vs Normal Distribution');
legend({'Empirical','Normal'},'Location','northeast');
hold off;
close;

figure(18);
ksdensity(JPMDailyReturns);
hold on;
JPMx = [-.1:.001:.1];
JPMy = normpdf(JPMx,JPMAverageDailyReturn,JPMStdReturns);
plot(JPMx,JPMy);
title('Empirical Density of JPM Returns vs Normal Distribution');
legend({'Empirical','Normal'},'Location','northeast');
hold off;
close;

figure(19);
ksdensity(KODailyReturns);
hold on;
KOx = [-.1:.001:.1];
KOy = normpdf(KOx,KOAverageDailyReturn,KOStdReturns);
plot(KOx,KOy);
title('Empirical Density of KO Returns vs Normal Distribution');
legend({'Empirical','Normal'},'Location','northeast');
hold off;
close;

figure(20);
ksdensity(NEMDailyReturns);
hold on;
NEMx = [-.1:.001:.1];
NEMy = normpdf(NEMx,NEMAverageDailyReturn,NEMStdReturns);
plot(NEMx,NEMy);
title('Empirical Density of NEM Returns vs Normal Distribution');
legend({'Empirical','Normal'},'Location','northeast');
hold off;
close;

figure(21);
ksdensity(PFEDailyReturns);
hold on;
PFEx = [-.1:.001:.1];
PFEy = normpdf(PFEx,PFEAverageDailyReturn,PFEStdReturns);
plot(PFEx,PFEy);
title('Empirical Density of PFE Returns vs Normal Distribution');
legend({'Empirical','Normal'},'Location','northeast');
hold off;
close;

figure(22);
ksdensity(PSXDailyReturns);
hold on;
PSXx = [-.1:.001:.1];
PSXy = normpdf(PSXx,PSXAverageDailyReturn,PSXStdReturns);
plot(PSXx,PSXy);
title('Empirical Density of PSX Returns vs Normal Distribution');
legend({'Empirical','Normal'},'Location','northeast');
hold off;
close;

%% Functions
function ResVar = CalcVariance(w,Sigma)
    ResVar = w'*Sigma*w;
end
