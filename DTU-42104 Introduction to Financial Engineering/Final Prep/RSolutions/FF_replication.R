FF_data = read.table("C:/Users/nilan/Dropbox/IFE2019/Exercises/Rstuff/FamaFrench_mon_69_98.txt", header = TRUE) #replace with relevant link
#install.packages('quantmod')
attach(FF_data)
#install.packages('Ecdat')
#install.packages('robust')
library(Ecdat)
#library(quantmod)
library(robust)
data(CRSPmon)
ge = 100*CRSPmon[,1] - RF
ibm = 100*CRSPmon[,2] - RF
mobil = 100*CRSPmon[,3] - RF
stocks=cbind(ge,ibm,mobil)
fit = lm(cbind(ge,ibm,mobil)~Mkt.RF+SMB+HML)
options(digits=3)
fit

##  Figure 18.7
pairs(cbind(ge,ibm,mobil,Mkt.RF,SMB,HML))
graphics.off()


cor(fit$residuals)
covRob(fit$residuals,cor=T)
cor.test(fit$residuals[,1], fit$residuals[,2])
cor.test(fit$residuals[,1], fit$residuals[,3])
cor.test(fit$residuals[,2], fit$residuals[,3])

## Figure 18.8
pairs(fit$residuals)
graphics.off()

#computing covariance marix using FF
sigF = as.matrix(var(cbind(Mkt.RF,SMB,HML)))
bbeta = as.matrix(fit$coef)
bbeta = t( bbeta[-1,])
n=dim(CRSPmon)[1]
sigeps = (n-1)/(n-4) * as.matrix((var(as.matrix(fit$resid))))
sigeps = diag(as.matrix(sigeps))
sigeps = diag(sigeps,nrow=3)
cov_equities = bbeta %*% sigF %*% t(bbeta) + sigeps

options(digits=5)
sigF
bbeta
sigeps
bbeta %*% sigF %*% t(bbeta)
cov_equities
cov(stocks)

