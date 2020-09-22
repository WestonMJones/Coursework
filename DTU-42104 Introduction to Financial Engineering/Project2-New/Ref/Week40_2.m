close all
clear
mu = [0.1;0.2];
rho = -0.5; % rerun this for different choices of rho. See how the shape changes.
Sigma = [[0.1^2 0.1*0.2*rho];[rho*0.1*0.2 0.2^2]];
std = sqrt(diag(Sigma));
rf = 0.02;
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


plot(EF_sigma, mu_vector, 'b','LineWidth', 2)
hold on
xlim([0 inf]);
ylim([mu_vector(1) mu_vector(end)])
plot( std(1),mu(1),'b--X','LineWidth',2, 'MarkerSize',30,...
'MarkerEdgeColor','black' )
plot( std(2),mu(2),'b--X','LineWidth',2, 'MarkerSize',30,...
'MarkerEdgeColor','black' )
GMV_PF = [sigma_gmv,mu_gmv]
plot( sigma_gmv,mu_gmv,'b--X','LineWidth',2, 'MarkerSize',30,...
'MarkerEdgeColor','green' )
xlabel('\sigma')
ylabel('\mu_P')
