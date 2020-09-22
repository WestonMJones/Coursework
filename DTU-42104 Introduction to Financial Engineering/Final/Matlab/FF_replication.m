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