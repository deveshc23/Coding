#2
set.seed(5)
n<-50
p<-0.667
x<-rbinom(n,5,p)
obs<-rep(0,6)
for(i in 1:n){
  obs[x[i]+1]=obs[x[i]+1]+1
}
prob<-dbinom(0:5,5,p)
c<-chisq.test(obs,p=prob)
p_c<-c$p.value

#3
set.seed(10)
n <- 100
lambda <- 2.5
x <- rpois(n, lambda)
mean(x)
var(x)
obs5 <- table(cut(x,
                  breaks = c(-1, 0, 1, 2, 3, Inf),
                  labels = FALSE))
prob5 <- c(dpois(0:3, lambda),
           1 - ppois(3, lambda))
test5 <- chisq.test(obs5, p = prob5)
p_value_5 <- test5$p.value
p_value_5

obs10 <- table(cut(x,
                   breaks = c(-1, 0:9, Inf),
                   labels = FALSE))
prob10 <- c(dpois(0:8, lambda),
            1 - ppois(8, lambda))
test10 <- chisq.test(obs10, p = prob10)
p_value_10 <- test10$p.value
p_value_10


