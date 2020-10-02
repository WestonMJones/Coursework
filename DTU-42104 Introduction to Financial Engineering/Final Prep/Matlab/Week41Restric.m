clear
% With no restictions to get a good starting point for the optimization
Week40_1
close
mu = [MCD_mean_a;KO_mean_a;MSFT_mean_a];
std = diag(Sigma).^0.5;
a = mu'/Sigma*mu;
b = mu'/Sigma*ones(3,1);
c = ones(3,1)'/Sigma*ones(3,1);
SigmaInv = inv(Sigma);
ParabolaCoeff = [a/(a*c-b^2) -2*b/(a*c-b^2) c/(a*c-b^2)];
w = SigmaInv*[mu ones(3,1)]*[[c -b];[-b a]]/((a*c-b^2));

mu_gmv = b/c;
sigma_gmv = (1/c)^0.5;
w_gmv = (1/c)*SigmaInv*ones(3,1);

Aeq = ones(1,3); % weights summing to 1
beq = 1;

Aeq(2,:) = (mu'); % expected return

ub = ones(3,1)/2; % restrictions on no more than 50% allocated
Sorted_mu =sort(mu);
Max = mean(Sorted_mu(end-1:end));
Min = mean(Sorted_mu(1:2));
options= optimset('Display','off');
for i=1:101
    ReqMean(i) = (Max-Min)/100*(i-1)+Min;
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
plot(EF_sigma,mu_vector) 
hold on
plot(sigma_P,ReqMean)


function ResVar = CalcVariance(w,Sigma)
    ResVar = w'*Sigma*w;
end







