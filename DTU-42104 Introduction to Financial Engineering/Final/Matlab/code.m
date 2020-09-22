% Question 4
mu = [.18; .16];
mu_e = mu - .02;

sigma = [.29^2, .05 * .29 * .24; .05 * .29 * .24, .24^2];

A = [mu, ones(2,1)]' * inv(sigma) * [mu, ones(2,1)];

a = mu' * inv(sigma) * mu;
b = mu' * inv(sigma) * ones(2,1);
c = ones(2,1)' * inv(sigma) * ones(2,1);

GMVu = b/c;
GMVstd = sqrt(1/c);
GMVw = (1/c) * inv(sigma) * ones(2,1);

TANu_e = (mu_e' * inv(sigma) * mu_e) / (ones(2,1)' * inv(sigma) * mu_e);
TANu = TANu_e + .02;
TANstd = sqrt(mu_e' * inv(sigma) * mu_e) / (ones(2,1)' * inv(sigma) * mu_e);
TANw = inv(sigma) * mu_e * (1/(ones(2,1)' * inv(sigma) * mu_e));

TANsharpe = TANu_e / TANstd;

%Question 5
weights = [.5; .5]

test = ((weights' * ((1.2+1.5)/2)^2) * .15^2) + (.5*.08^2) + (.5*.15^2)

% ([.5; .5] * (1.2+1.5 / 2))^2 * .15^2)               +      (.5 * .08^2) + (.5 * .15^2) = 

