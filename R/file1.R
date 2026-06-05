n<-5
p<-0.66
values<-rbinom(50,n,p)
breaks<-c(0:5)
obs<-table(factor(values,levels=0:5))
obs
expected<-50*dbinom(0:5,n,p)
chi<-0
chi<-sum((obs-expected)^2/expected)
df <- 5
p_value <- 1 - pchisq(chi, df)
p_value

n<-100
values<-rpois(n,lambda=2.5)
breaks<-c(0:4,Inf)
obs<-table(cut(values,
               breaks=breaks,
               right=FALSE,
               include.lowest=TRUE))
expected <- c(
  dpois(0,2.5),
  dpois(1,2.5),
  dpois(2,2.5),
  dpois(3,2.5),
  1 - ppois(3,2.5)
)
chi <- chisq.test(
  x = obs,
  p = expected,
  rescale.p = TRUE,
  correct = FALSE
)

chi$p.value
