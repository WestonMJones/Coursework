load('FFdataFromR.mat')
% Note that everything is multiplied with 100!
ge = 100*stockdata.ge - FFdata.RF;
ibm = 100*stockdata.ibm - FFdata.RF;
mobil = 100*stockdata.mobil - FFdata.RF;
stocks= [ge ibm mobil];
fit1 = LinearModel.fit([FFdata.MktRF FFdata.SMB FFdata.HML],stocks(:,1));
fit2 = LinearModel.fit([FFdata.MktRF FFdata.SMB FFdata.HML],stocks(:,2));
fit3 = LinearModel.fit([FFdata.MktRF FFdata.SMB FFdata.HML],stocks(:,3));

fit1
fit2
fit3

%Figure 18.7
pairs([ge ibm mobil FFdata.MktRF FFdata.SMB FFdata.HML], {'ge', 'ibm', 'xom', 'mkt', 'smb', 'hml'})


corr([fit1.Residuals.Raw fit2.Residuals.Raw fit3.Residuals.Raw])
[R,P, UL, LB] = corrcoef([fit1.Residuals.Raw fit2.Residuals.Raw fit3.Residuals.Raw])

%Figure 18.8
pairs([fit1.Residuals.Raw fit2.Residuals.Raw fit3.Residuals.Raw], {'ge', 'ibm', 'xom'})

%computing covariance marix using FF
sigF = cov([FFdata.MktRF FFdata.SMB FFdata.HML]);
bbeta = ([[fit1.Coefficients.Estimate(2:4)]';[fit2.Coefficients.Estimate(2:4)]';[fit3.Coefficients.Estimate(2:4)]'])';
n=size(FFdata.RF,1);
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
Acov_FF = 12*cov_equities/10000
Acov = 12*cov(stocks)/10000

% Using only CAPM-part
fit1_C = LinearModel.fit([FFdata.MktRF],stocks(:,1));
fit2_C = LinearModel.fit([FFdata.MktRF],stocks(:,2));
fit3_C = LinearModel.fit([FFdata.MktRF],stocks(:,3));

fit1_C
fit2_C
fit3_C

%Figure 18.7
pairs([ge ibm mobil FFdata.MktRF] , {'ge', 'ibm', 'xom', 'mkt'})

corr([fit1_C.Residuals.Raw fit2_C.Residuals.Raw fit3_C.Residuals.Raw])
[R,P, UL, LB] = corrcoef([fit1_C.Residuals.Raw fit2_C.Residuals.Raw fit3_C.Residuals.Raw])



% Figure 18.8
pairs([fit1_C.Residuals.Raw fit2_C.Residuals.Raw fit3_C.Residuals.Raw],{'ge', 'ibm', 'xom'})

%computing covariance marix using FF
sigFCAPM = cov([FFdata.MktRF]);
bbetaCAPM = ([[fit1_C.Coefficients.Estimate(2)]';[fit2_C.Coefficients.Estimate(2)]';[fit3_C.Coefficients.Estimate(2)]'])';
n=size(FFdata.RF,1);
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
Acov_FFCAPM = 12*cov_equitiesCAPM/10000

