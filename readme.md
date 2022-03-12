# 알고리즘 레포트


## 알고리즘 시간 복잡도
![image](https://user-images.githubusercontent.com/100903674/158020725-84b87c9a-edad-41e6-8a0e-03edbd0f9889.png)9O9

o(log n)< o(n)<o(nlogn)<o(n^2)<o(2^n)
### 점근적 표기법

* **O 표기 :상한 표기법**

점근적 하한만을 알고 있을때 사용하는 표기법

g(n),f(n)은 양수 n의 값에 따라 달라지는 함수

f(n)=o(g(n))= {f(n):모든 n>=k에 대해 0<=f(n)<=c*g(n)인 양의 함수이며 양수 c 그리고 k가 존재하는 함수}


ex) f(n)=2n+3 g(n)=n일떄
f(n)=o(g(n))임을 증명(
f(n)|c*g(n)|f(n)<=c*g(n)이고 n>=k을 만족하는 양의 정수 k를 가질때이것의 진위 T/F
---|---|---|
2n+3|1*n|F
2n+3|2*n|F
2n+3|3*n|T

![image](https://user-images.githubusercontent.com/100903674/158021908-f53de5dc-c07f-4882-8f11-824602f33f65.png)




* **Ω 표기:하한 표기법**

* f(n)=Ω((g))={f(n): 모든 n>=k에 대해 0<=c*g(n)<=f(n)인 양의 함수이며 c 그리고 k가 존재하는 함수)


* **Θ 표기**

f(n)=Θ((g))={f(n): 모든 n>=k에 대해 0<=c*g(n)<=f(n)<=i*g(n)인 양의 함수이며 c, k,i가 존재하는 함수)
