load DataWeek40.mat
KO.Returns = NaN*ones(length(KO.Date),1);
KO.Returns(2:end) = (KO.AdjClose(2:end)-KO.AdjClose(1:end-1))./KO.AdjClose(1:end-1);
MCD.Returns = NaN*ones(length(MCD.Date),1);
MCD.Returns(2:end) = (MCD.AdjClose(2:end)-MCD.AdjClose(1:end-1))./MCD.AdjClose(1:end-1);
MSFT.Returns = NaN*ones(length(MSFT.Date),1);
MSFT.Returns(2:end) = (MSFT.AdjClose(2:end)-MSFT.AdjClose(1:end-1))./MSFT.AdjClose(1:end-1);

% Mean and annualising
KO_mean_w = geomean(1+KO.Returns(2:end))-1;
KO_mean_a = (1+KO_mean_w)^52-1;

MCD_mean_w = geomean(1+MCD.Returns(2:end))-1;
MCD_mean_a = (1+MCD_mean_w)^52-1;

MSFT_mean_w = geomean(1+MSFT.Returns(2:end))-1;
MSFT_mean_a = (1+MSFT_mean_w)^52-1;

% Covariance matrix including annualising
VarCovar = cov([ MCD.Returns(2:end) KO.Returns(2:end) MSFT.Returns(2:end)])*52;

% Portfolio 1 - Risky-assets only min. variance
mu = u_all'; %matrix of returns
Sigma = Correlation; %correlation matrix
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

figure(9)
mu_vector = (min(mu) - range(mu)):0.001:(max(mu) + range(mu));
EF_sigma = ((c*mu_vector.^2-2*b*mu_vector + a)/(a*c-b^2)).^(1/2);
plot(EF_sigma,mu_vector);
hold on
plot(sigma_P,ReqMean);
close;


w_p1 = w_gmv_SS;
u_p1 = dot(w_p1,u_all);
var_p1 = w_p1'*Correlation*w_p1;