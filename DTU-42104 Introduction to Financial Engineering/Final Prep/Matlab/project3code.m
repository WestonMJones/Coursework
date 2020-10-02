%% Import Stock Data

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
% CSCO_new = readtable(".\Data\CSCO_new.csv", opts);
% FDX_new = readtable(".\Data\FDX_new.csv", opts);
% GOOG_new = readtable(".\Data\GOOG_new.csv", opts);
% JPM_new = readtable(".\Data\JPM_new.csv", opts);
% KO_new = readtable(".\Data\KO_new.csv", opts);
% NEM_new = readtable(".\Data\NEM_new.csv", opts);
% PFE_new = readtable(".\Data\PFE_new.csv", opts);
% PSX_new = readtable(".\Data\PSX_new.csv", opts);

%% Load of FF-Data
load('FFDaily.mat')

FFDaily(1,:) =[];

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

DailyReturns_all = [CSCODailyReturns, FDXDailyReturns, GOOGDailyReturns, JPMDailyReturns, KODailyReturns, NEMDailyReturns, PFEDailyReturns, PSXDailyReturns];

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

AnnualAverageReturn_all = [CSCOAnnualAverageReturn; FDXAnnualAverageReturn; GOOGAnnualAverageReturn; JPMAnnualAverageReturn; KOAnnualAverageReturn; NEMAnnualAverageReturn; PFEAnnualAverageReturn; PSXAnnualAverageReturn];


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

%% Fitting CAPM
Stocks = ["CSCO","FDX","GOOG","JPM","KO","NEM","PFE","PSX"];
DailyReturns_all;

Stocks_fit = 100*DailyReturns_all-FFDaily.RF;
    
fit1_CAPM = LinearModel.fit([FFDaily.MktRF],Stocks_fit(:,1));
fit2_CAPM = LinearModel.fit([FFDaily.MktRF],Stocks_fit(:,2));
fit3_CAPM = LinearModel.fit([FFDaily.MktRF],Stocks_fit(:,3));
fit4_CAPM = LinearModel.fit([FFDaily.MktRF],Stocks_fit(:,4));
fit5_CAPM = LinearModel.fit([FFDaily.MktRF],Stocks_fit(:,5));
fit6_CAPM = LinearModel.fit([FFDaily.MktRF],Stocks_fit(:,6));
fit7_CAPM = LinearModel.fit([FFDaily.MktRF],Stocks_fit(:,7));
fit8_CAPM = LinearModel.fit([FFDaily.MktRF],Stocks_fit(:,8));

    %% Figure 18.7

%All 8 stocks 
%pairs([Stocks_fit FFDaily.MktRF],{'CSCO','FDX','GOOG','JPM','KO','NEM','PFE','PSX', 'mkt'})
pairs([Stocks_fit FFDaily.MktRF])

%Divided, however we lose some correlation plots between the stocks
%pairs([Stocks_fit(:,1:4) FFDaily.MktRF],{'CSCO','FDX','GOOG','JPM', 'mkt'})
%pairs([Stocks_fit(:,5:8) FFDaily.MktRF],{'KO','NEM','PFE','PSX', 'mkt'})


cor_res_CAPM = corr([fit1_CAPM.Residuals.Raw fit2_CAPM.Residuals.Raw fit3_CAPM.Residuals.Raw fit4_CAPM.Residuals.Raw fit5_CAPM.Residuals.Raw fit6_CAPM.Residuals.Raw fit7_CAPM.Residuals.Raw fit8_CAPM.Residuals.Raw]);
[R,P, UL, LB] = corrcoef([fit1_CAPM.Residuals.Raw fit2_CAPM.Residuals.Raw fit3_CAPM.Residuals.Raw fit4_CAPM.Residuals.Raw fit5_CAPM.Residuals.Raw fit6_CAPM.Residuals.Raw fit7_CAPM.Residuals.Raw fit8_CAPM.Residuals.Raw]);

    %% Figure 18.8
%pairs([fit1_CAPM.Residuals.Raw fit2_CAPM.Residuals.Raw fit3_CAPM.Residuals.Raw fit4_CAPM.Residuals.Raw fit5_CAPM.Residuals.Raw fit6_CAPM.Residuals.Raw fit7_CAPM.Residuals.Raw fit8_CAPM.Residuals.Raw], {'CSCO','FDX','GOOG','JPM','KO','NEM','PFE','PSX'})
pairs([fit1_CAPM.Residuals.Raw fit2_CAPM.Residuals.Raw fit3_CAPM.Residuals.Raw fit4_CAPM.Residuals.Raw fit5_CAPM.Residuals.Raw fit6_CAPM.Residuals.Raw fit7_CAPM.Residuals.Raw fit8_CAPM.Residuals.Raw])

row1 = ["",Stocks];
row2 = ["Intercept", fit1_CAPM.Coefficients.Estimate(1), fit2_CAPM.Coefficients.Estimate(1), fit3_CAPM.Coefficients.Estimate(1),fit4_CAPM.Coefficients.Estimate(1),fit5_CAPM.Coefficients.Estimate(1),fit6_CAPM.Coefficients.Estimate(1),fit7_CAPM.Coefficients.Estimate(1),fit8_CAPM.Coefficients.Estimate(1)];
row3 = ["Mkt.RF", fit1_CAPM.Coefficients.Estimate(2), fit2_CAPM.Coefficients.Estimate(2), fit3_CAPM.Coefficients.Estimate(2),fit4_CAPM.Coefficients.Estimate(2),fit5_CAPM.Coefficients.Estimate(2),fit6_CAPM.Coefficients.Estimate(2),fit7_CAPM.Coefficients.Estimate(2),fit8_CAPM.Coefficients.Estimate(2)];
T_inter_CAPM = [row1;row2;row3];

%% Fitting FF

fit1 = LinearModel.fit([FFDaily.MktRF FFDaily.SMB FFDaily.HML],Stocks_fit(:,1));
fit2 = LinearModel.fit([FFDaily.MktRF FFDaily.SMB FFDaily.HML],Stocks_fit(:,2));
fit3 = LinearModel.fit([FFDaily.MktRF FFDaily.SMB FFDaily.HML],Stocks_fit(:,3));
fit4 = LinearModel.fit([FFDaily.MktRF FFDaily.SMB FFDaily.HML],Stocks_fit(:,4));
fit5 = LinearModel.fit([FFDaily.MktRF FFDaily.SMB FFDaily.HML],Stocks_fit(:,5));
fit6 = LinearModel.fit([FFDaily.MktRF FFDaily.SMB FFDaily.HML],Stocks_fit(:,6));
fit7 = LinearModel.fit([FFDaily.MktRF FFDaily.SMB FFDaily.HML],Stocks_fit(:,7));
fit8 = LinearModel.fit([FFDaily.MktRF FFDaily.SMB FFDaily.HML],Stocks_fit(:,8));

    %% Figure 18.7

%All 8 stocks 
%pairs([Stocks_fit FFDaily.MktRF FFDaily.SMB FFDaily.HML],{'CSCO','FDX','GOOG','JPM','KO','NEM','PFE','PSX', 'mkt', 'smb', 'hml'})
pairs([Stocks_fit FFDaily.MktRF FFDaily.SMB FFDaily.HML])

%Divided, however we lose some correlation plots between the stocks
%pairs([Stocks_fit(:,1:4) FFDaily.MktRF FFDaily.SMB FFDaily.HML],{'CSCO','FDX','GOOG','JPM', 'mkt', 'smb', 'hml'})
%pairs([Stocks_fit(:,5:8) FFDaily.MktRF FFDaily.SMB FFDaily.HML],{'KO','NEM','PFE','PSX', 'mkt', 'smb', 'hml'})


cor_res_FF = corr([fit1.Residuals.Raw fit2.Residuals.Raw fit3.Residuals.Raw fit4.Residuals.Raw fit5.Residuals.Raw fit6.Residuals.Raw fit7.Residuals.Raw fit8.Residuals.Raw]);
[R_FF,P_FF, UB_FF, LB_FF] = corrcoef([fit1.Residuals.Raw fit2.Residuals.Raw fit3.Residuals.Raw fit4.Residuals.Raw fit5.Residuals.Raw fit6.Residuals.Raw fit7.Residuals.Raw fit8.Residuals.Raw]);

    %% Figure 18.8
%pairs([fit1.Residuals.Raw fit2.Residuals.Raw fit3.Residuals.Raw fit4.Residuals.Raw fit5.Residuals.Raw fit6.Residuals.Raw fit7.Residuals.Raw fit8.Residuals.Raw], {'CSCO','FDX','GOOG','JPM','KO','NEM','PFE','PSX'})
pairs([fit1.Residuals.Raw fit2.Residuals.Raw fit3.Residuals.Raw fit4.Residuals.Raw fit5.Residuals.Raw fit6.Residuals.Raw fit7.Residuals.Raw fit8.Residuals.Raw])

%% Empirical testing of CAPM 
for i = 1:8
    mdl = LinearModel.fit([FFDaily.MktRF],DailyReturns_all(:,i));
    alpha(i) = mdl.Coefficients.Estimate(1);
    betaCAPM(i) = mdl.Coefficients.Estimate(2);
    specific(i) = mdl.MSE;
end
scatter(betaCAPM*100,AnnualAverageReturn_all)

mdl = LinearModel.fit(betaCAPM,AnnualAverageReturn_all);
intercept = mdl.Coefficients.Estimate(1);
slope = mdl.Coefficients.Estimate(2);
hold on
plot([ 0 betaCAPM*100 1.5],intercept + [0 betaCAPM 0.015]*slope)
c = Stocks;
dx = 0.03; dy = 0; % displacement so the text does not overlay the data points
text(betaCAPM*100+dx, AnnualAverageReturn_all+dy, c);
xlabel('\beta')
ylabel('Return')

%% Interpretation of FF

row1 = ["",Stocks];
row2 = ["Intercept", fit1.Coefficients.Estimate(1), fit2.Coefficients.Estimate(1), fit3.Coefficients.Estimate(1),fit4.Coefficients.Estimate(1),fit5.Coefficients.Estimate(1),fit6.Coefficients.Estimate(1),fit7.Coefficients.Estimate(1),fit8.Coefficients.Estimate(1)];
row3 = ["Mkt.RF", fit1.Coefficients.Estimate(2), fit2.Coefficients.Estimate(2), fit3.Coefficients.Estimate(2),fit4.Coefficients.Estimate(2),fit5.Coefficients.Estimate(2),fit6.Coefficients.Estimate(2),fit7.Coefficients.Estimate(2),fit8.Coefficients.Estimate(2)];
row4 = ["SMB", fit1.Coefficients.Estimate(3), fit2.Coefficients.Estimate(3), fit3.Coefficients.Estimate(3),fit4.Coefficients.Estimate(3),fit5.Coefficients.Estimate(3),fit6.Coefficients.Estimate(3),fit7.Coefficients.Estimate(3),fit8.Coefficients.Estimate(3)];
row5 = ["HML", fit1.Coefficients.Estimate(4), fit2.Coefficients.Estimate(4), fit3.Coefficients.Estimate(4),fit4.Coefficients.Estimate(4),fit5.Coefficients.Estimate(4),fit6.Coefficients.Estimate(4),fit7.Coefficients.Estimate(4),fit8.Coefficients.Estimate(4)];
row6 = ["Growth/Wealth", "Growth", "Value", "Growth", "Value", "TBD", "Value", "Growth", "Value"];
row7 = ["Large/Small", "Large", "Small", "Large", "Large", "Large", "Small", "Large", "TBD"];

T_inter_FF = [row1;row2;row3;row4;row5;row6;row7];

%% Computing covariance marix using FF - FamaFrench
sigF = cov([FFDaily.MktRF FFDaily.SMB FFDaily.HML]);
bbeta = ([[fit1.Coefficients.Estimate(2:4)]';[fit2.Coefficients.Estimate(2:4)]';[fit3.Coefficients.Estimate(2:4)]';[fit4.Coefficients.Estimate(2:4)]';[fit5.Coefficients.Estimate(2:4)]';[fit6.Coefficients.Estimate(2:4)]';[fit7.Coefficients.Estimate(2:4)]';[fit8.Coefficients.Estimate(2:4)]'])';
n=size(FFDaily.RF,1);
sigeps = (n-1)/(n-4) * cov([fit1.Residuals.Raw fit2.Residuals.Raw fit3.Residuals.Raw fit4.Residuals.Raw fit5.Residuals.Raw fit6.Residuals.Raw fit7.Residuals.Raw fit8.Residuals.Raw]);
sigeps = diag(diag(sigeps));
cov_equities = bbeta' * sigF * bbeta + sigeps;

% in Annual terms and scaling again
Acov_FF = cov_equities*252/10000 %Scaled with number of trading days and annulized by 100^2
Acov = cov(Stocks_fit)*252/10000 %Scaled with number of trading days and annulized by 100^2
%% Computing covariance marix using FF - CAPM
sigFCAPM = cov([FFDaily.MktRF]);
bbetaCAPM = ([[fit1_CAPM.Coefficients.Estimate(2)]';[fit2_CAPM.Coefficients.Estimate(2)]';[fit3_CAPM.Coefficients.Estimate(2)]';[fit4_CAPM.Coefficients.Estimate(2)]';[fit5_CAPM.Coefficients.Estimate(2)]';[fit6_CAPM.Coefficients.Estimate(2)]';[fit7_CAPM.Coefficients.Estimate(2)]';[fit8_CAPM.Coefficients.Estimate(2)]'])';
n=size(FFDaily.RF,1);
sigepsCAPM = (n-1)/(n-2) * cov([fit1_CAPM.Residuals.Raw fit2_CAPM.Residuals.Raw fit3_CAPM.Residuals.Raw fit4_CAPM.Residuals.Raw fit5_CAPM.Residuals.Raw fit6_CAPM.Residuals.Raw fit7_CAPM.Residuals.Raw fit8_CAPM.Residuals.Raw]);
sigepsCAPM = diag(diag(sigepsCAPM));
cov_equitiesCAPM = bbetaCAPM' * sigFCAPM * bbetaCAPM + sigepsCAPM;

% in Annual terms
Acov_FFCAPM = cov_equitiesCAPM*252/10000 %Scaled with number of trading days and annulized by 100^2
%% Efficient Frontiers

mu = AnnualAverageReturn_all
mu_vector = (min(mu) - range(mu)):0.001:(max(mu) + range(mu));

Sigma = Acov;
sd = sqrt(diag(Sigma));
a = mu'/Sigma*mu;
b = mu'/Sigma*ones(8,1);
c = ones(8,1)'/Sigma*ones(8,1);

%GMV
SigmaInv = inv(Sigma);
mu_gmv = b/c;
sigma_gmv = (1/c)^0.5;
w_gmv = (1/c)*SigmaInv*ones(8,1);

%Tangent
mu_tan = (mu'*SigmaInv*mu)/(ones(8,1)'*SigmaInv*mu);
sigma_tan = sqrt(mu'*SigmaInv*mu)/(ones(8,1)'*SigmaInv*mu);
w_tan = (SigmaInv*mu)/(ones(8,1)'*SigmaInv*mu);

%EF stocks
EF_sigma = ((c*mu_vector.^2-2*b*mu_vector + a)/(a*c-b^2)).^(1/2);

%EF FF
Sigma = Acov_FF;
sd = sqrt(diag(Sigma));
a = mu'/Sigma*mu;
b = mu'/Sigma*ones(8,1);
c = ones(8,1)'/Sigma*ones(8,1);
EF_sigma_FF = ((c*mu_vector.^2-2*b*mu_vector + a)/(a*c-b^2)).^(1/2);

%EF CAPM
Sigma = Acov_FFCAPM;
sd = sqrt(diag(Sigma));
a = mu'/Sigma*mu;
b = mu'/Sigma*ones(8,1);
c = ones(8,1)'/Sigma*ones(8,1);
EF_sigma_FFCAPM = ((c*mu_vector.^2-2*b*mu_vector + a)/(a*c-b^2)).^(1/2);

% Plot of three Efficient Frontiers and two portfolios (GMV and tangent)
plot(EF_sigma,mu_vector) 
hold on
plot(EF_sigma_FFCAPM,mu_vector)
plot(EF_sigma_FF,mu_vector)
plot(sigma_gmv,mu_gmv,'b--X','LineWidth',2, 'MarkerSize',15,'MarkerEdgeColor','green' ) % GMV portfolio
plot(sigma_tan,mu_tan,'b--X','LineWidth',2, 'MarkerSize',15,'MarkerEdgeColor','red' ) % Tangent portfolio
plot( sd(1),mu(1),'b--X','LineWidth',1, 'MarkerSize',10,'MarkerEdgeColor','blue' )
plot( sd(2),mu(2),'b--X','LineWidth',1, 'MarkerSize',10,'MarkerEdgeColor','blue' )
plot( sd(3),mu(3),'b--X','LineWidth',1, 'MarkerSize',10,'MarkerEdgeColor','blue' )
plot( sd(4),mu(4),'b--X','LineWidth',1, 'MarkerSize',10,'MarkerEdgeColor','blue' )
plot( sd(5),mu(5),'b--X','LineWidth',1, 'MarkerSize',10,'MarkerEdgeColor','blue' )
plot( sd(6),mu(6),'b--X','LineWidth',1, 'MarkerSize',10,'MarkerEdgeColor','blue' )
plot( sd(7),mu(7),'b--X','LineWidth',1, 'MarkerSize',10,'MarkerEdgeColor','blue' )
plot( sd(8),mu(8),'b--X','LineWidth',1, 'MarkerSize',10,'MarkerEdgeColor','blue' )
c = Stocks;
dx = 0.005; dy = 0.00; % displacement so the text does not overlay the data points
text(sd+dx, mu+dy, c)
legend('EF stocks','EF CAPM', 'EF FF', 'GMV', 'TAN')
xlabel('\sigma')
ylabel('\mu_P')
xlim([0 0.4])
hold off

%% Diversification Effects
ztotal_variances = var(DailyReturns_all);
zmarket_risk = (betaCAPM.^2)*var(FFDaily.MktRF);
zunique_risk = ztotal_variances - zmarket_risk;
zunique_risk_avg = mean(zunique_risk);
zunique_risk_portfolio = zunique_risk_avg / 8;
zstdportfolio = sqrt(zunique_risk_avg) / sqrt(8);
zstdavg = sqrt(zunique_risk_avg);
zratio = zstdportfolio / zstdavg;





%% Rolling Estimate
betas = [];
count = 1;

for i = 252:1:1257
    returns_slice = DailyReturns_all(count:i,1:8);
   
    for j = 1:8
        mdl = LinearModel.fit([FFDaily.MktRF(count:i)],returns_slice(:,j));
        betas(count,j) = 100 * mdl.Coefficients.Estimate(2);
    end
    
    count = count+1;
end
p = plot(betas);
set(p,{'Marker'},{'+';'+';'+';'+';'+';'+';'+';'o';});
legend('CSCO','FDX','GOOG','JPM','KO','NEM','PFE','PSX','Location','SouthEast');
xlabel('Days since Jan 2nd, 2015','FontSize',12,'FontWeight','bold'); 
ylabel('Rolling Beta Predictions','FontSize',12,'FontWeight','bold');
title('Beta Predictions');
close;
