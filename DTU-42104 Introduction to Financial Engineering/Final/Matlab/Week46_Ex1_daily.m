load('FFDaily6310.mat')
% Note that everything is multiplied with 100!
StockData =  hist_stock_data('28061963','29052010', {'GE', 'IBM', 'XOM'}, 'frequency','d');
ge = 100*diff(StockData(1).AdjClose)./StockData(1).AdjClose(1:end-1) - FamaFrenchDaily.RF;
ibm = 100*diff(StockData(2).AdjClose)./StockData(2).AdjClose(1:end-1) - FamaFrenchDaily.RF;
mobil = 100*diff(StockData(3).AdjClose)./StockData(3).AdjClose(1:end-1) - FamaFrenchDaily.RF;
stocks= [ge ibm mobil];
fit1 = LinearModel.fit([FamaFrenchDaily.MktRF FamaFrenchDaily.SMB FamaFrenchDaily.HML],stocks(:,1));
fit2 = LinearModel.fit([FamaFrenchDaily.MktRF FamaFrenchDaily.SMB FamaFrenchDaily.HML],stocks(:,2));
fit3 = LinearModel.fit([FamaFrenchDaily.MktRF FamaFrenchDaily.SMB FamaFrenchDaily.HML],stocks(:,3));

fit1
fit2
fit3

%Figure 18.7
pairs([ge ibm mobil FamaFrenchDaily.MktRF FamaFrenchDaily.SMB FamaFrenchDaily.HML], {'ge', 'ibm', 'xom', 'mkt', 'smb', 'hml'})


corr([fit1.Residuals.Raw fit2.Residuals.Raw fit3.Residuals.Raw])
[R,P, UL, LB] = corrcoef([fit1.Residuals.Raw fit2.Residuals.Raw fit3.Residuals.Raw])

%Figure 18.8
pairs([fit1.Residuals.Raw fit2.Residuals.Raw fit3.Residuals.Raw], {'ge', 'ibm', 'xom'})

%computing covariance marix using FF
sigF = cov([FamaFrenchDaily.MktRF FamaFrenchDaily.SMB FamaFrenchDaily.HML]);
bbeta = ([[fit1.Coefficients.Estimate(2:4)]';[fit2.Coefficients.Estimate(2:4)]';[fit3.Coefficients.Estimate(2:4)]'])';
n=size(FamaFrenchDaily.RF,1);
sigeps = (n-1)/(n-4) * cov([fit1.Residuals.Raw fit2.Residuals.Raw fit3.Residuals.Raw]);
sigeps = diag(diag(sigeps));
cov_equities = bbeta' * sigF * bbeta + sigeps;

sigF
bbeta
sigeps
bbeta' * sigF *(bbeta)
cov_equities
cov(stocks)

% in Annual terms and scaling again
Acov_FF = 252*cov_equities/10000
Acov = 252*cov(stocks)/10000

% Using only CAPM-part
fit1_C = LinearModel.fit([FamaFrenchDaily.MktRF],stocks(:,1));
fit2_C = LinearModel.fit([FamaFrenchDaily.MktRF],stocks(:,2));
fit3_C = LinearModel.fit([FamaFrenchDaily.MktRF],stocks(:,3));

fit1_C
fit2_C
fit3_C

%Figure 18.7
pairs([ge ibm mobil FamaFrenchDaily.MktRF] , {'ge', 'ibm', 'xom', 'mkt'})

corr([fit1_C.Residuals.Raw fit2_C.Residuals.Raw fit3_C.Residuals.Raw])
[R,P, UL, LB] = corrcoef([fit1_C.Residuals.Raw fit2_C.Residuals.Raw fit3_C.Residuals.Raw])



% Figure 18.8
pairs([fit1_C.Residuals.Raw fit2_C.Residuals.Raw fit3_C.Residuals.Raw],{'ge', 'ibm', 'xom'})

%computing covariance marix using FF
sigFCAPM = cov([FamaFrenchDaily.MktRF]);
bbetaCAPM = ([[fit1_C.Coefficients.Estimate(2)]';[fit2_C.Coefficients.Estimate(2)]';[fit3_C.Coefficients.Estimate(2)]'])';
n=size(FamaFrenchDaily.RF,1);
sigepsCAPM = (n-1)/(n-2) * cov([fit1_C.Residuals.Raw fit2_C.Residuals.Raw fit3_C.Residuals.Raw]);
sigepsCAPM = diag(diag(sigepsCAPM));
cov_equitiesCAPM = bbetaCAPM' * sigFCAPM * bbetaCAPM + sigepsCAPM;

sigFCAPM
bbetaCAPM
sigepsCAPM
bbetaCAPM' *sigFCAPM *(bbetaCAPM)
cov_equitiesCAPM
cov(stocks)

% in Annual terms
Acov_FFCAPM = 252*cov_equitiesCAPM/10000