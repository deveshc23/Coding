n0<-10
k<-0.1
del_t<-0.005
t<-60
simul<-function(k,n0,del_t,t){
  steps<-ceiling(t/del_t)
  times<-seq(0,t,by=del_t)
  A<-numeric(length(times))
  A[1]<-n0
  for(i in 1:(length(times)-1)){
    r<-runif(1,0,1)
    if(r<=A[i]*k*del_t){
      A[i+1]<-A[i]-1
    }
    else{
      A[i+1]<-A[i]
    }
    if(A[i+1]<0){
      A[i+1]<-0
    }
  }
  return(data.frame(time=times,molecules=A))
}
trial1 <- simul(k, n0, del_t, t)
trial2 <- simul(k, n0, del_t, t)
plot(trial1$time, trial1$molecules, type = "s", col = "blue", 
     xlab = "Time (sec)", ylab = "Number of molecules A(t)",
     main = "Naive SSA: Two Realizations (k=0.1, n0=20)")
lines(trial2$time, trial2$molecules, type = "s", col = "red")
legend("topright", legend=c("Realization 1", "Realization 2"), 
       col=c("blue", "red"), lty=1)
