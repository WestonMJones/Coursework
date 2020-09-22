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

count = 1;

for i=0:0.1:1 % Alloocation of asset 1 from 0 to 1
  for j = 0:0.1:(1-i) % Allocation of asset 2 up to what is not used by asset 1
      k = 1-i-j; % Allocation of asset 3 is the rest
      PF_mean_return(count,1) = i*MCD_mean_a + j*KO_mean_a + k*MSFT_mean_a;
      PF_std_return(count,1) = sqrt([i j k]*VarCovar*[i j k]');
      PF_w(count,:) = [i j k];
      count= count+1;
  end
end


[max_return, max_index] = max(PF_mean_return);

%Could have just taken MSFT. Can't get a higher return
PF_w(max_index,:)

[min_risk, min_index] = min(PF_std_return);

%calculations were needed to solve this

PF_w(min_index,:)

[SR, SR_index] = max(PF_mean_return./PF_std_return);

% Sharpe-Ratio portfolio

PF_w(SR_index,:)

scatter(PF_std_return, PF_mean_return)

%close all
%clear
mu = [MCD_mean_a;KO_mean_a;MSFT_mean_a];
Sigma = VarCovar;
std = sqrt(diag(Sigma));
a = mu'/Sigma*mu;
b = mu'/Sigma*ones(size(mu,1),1);
c = ones(size(mu,1),1)'/Sigma*ones(size(mu,1),1);
SigmaInv = inv(Sigma);
ParabolaCoeff = [a/(a*c-b^2) -2*b/(a*c-b^2) c/(a*c-b^2)];

mu_gmv = b/c;
sigma_gmv = (1/c)^0.5;
w_gmv = (1/c)*SigmaInv*ones(size(mu,1),1);

   
mu_vector = (min(mu) - range(mu)):0.001:(max(mu) + range(mu));

EF_sigma = ((c*mu_vector.^2-2*b*mu_vector + a)/(a*c-b^2)).^(1/2);
EF_sigma2 = ((c*mu_vector.^2-2*b*mu_vector + a)/(a*c-b^2));

hold on
plot(EF_sigma, mu_vector, 'b','LineWidth', 2)
hold on
xlim([0 inf]);
ylim([mu_vector(1) mu_vector(end)])
plot( std(1),mu(1),'b--X','LineWidth',2, 'MarkerSize',30,...
'MarkerEdgeColor','black' )
plot( std(2),mu(2),'b--X','LineWidth',2, 'MarkerSize',30,...
'MarkerEdgeColor','black' )
plot( std(3),mu(3),'b--X','LineWidth',2, 'MarkerSize',30,...
'MarkerEdgeColor','black' )
GMV_PF = [sigma_gmv,mu_gmv]
plot( sigma_gmv,mu_gmv,'b--X','LineWidth',2, 'MarkerSize',30,...
'MarkerEdgeColor','green' )
xlabel('\sigma')
ylabel('\mu_P')

% Comment: 3rd asset very close to being efficient
% Two other assets are not.
% The dots represent the portfolios defined in the text. None of them
% include shortselling. The portfolios on the EF could include
% shortselling. 
