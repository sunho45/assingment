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

![image](https://user-images.githubusercontent.com/100903674/158021978-7c26edd8-8684-4f94-9da7-766157fb0bb5.png)


위의 그래프를 보면 양의정수 c=3, 교점인 k=3 에서 n>=k일때 f(n)<=c*g(n)을 만족시키므로 f(n)=o(g(n))을 만족시킨다


* **Ω 표기:하한 표기법**

* f(n)=Ω(g(n))={f(n): 모든 n>=k에 대해 0<=c*g(n)<=f(n)인 양의 함수이며 c 그리고 k가 존재하는 함수)

ex) f(n)=2n^2+5 g(n)=n^2일때 

f(n)=Ω((g)) 임을 증명

f(n)|c*g(n)|f(n)>=c*g(n)이고 n>=k을 만족하는 양의 정수 k를 가질때이것의 진위 T/F
---|---|---|
2n^2+5|1*n^2|T

![image](https://user-images.githubusercontent.com/100903674/158022517-2986dde4-16ec-4bc9-8536-9b89dd60bd83.png)

위의 그래프를 보면 양의 정수 c=1에서 f(n)>=c*g(n)을 K=1일때 n>=k일때 f(n)>=c*g(n)을 만족시키므로 f(n)=Ω(g(n))을 만족시킨다.
* **Θ 표기**

f(n)=Θ((g))={f(n): 모든 n>=k에 대해 0<=c*g(n)<=f(n)<=i*g(n)인 양의 함수이며 c, k,i가 존재하는 함수)

f(n)=2n^2 g(n)=n^2일때

f(n)=Θ((g))임을 증명

일단c*g(n)<=f(n)을 증명해야한다.

f(n)|c*g(n)|f(n)>=c*g(n)이고 n>=k을 만족하는 양의 정수 k를 가질때이것의 진위 T/F
---|---|---|
2n^2|1*n^2|T

![image](https://user-images.githubusercontent.com/100903674/158025435-af153be7-6333-45ef-9f59-51a5d670136f.png)


위의 그래프를 보면 양의 정수 c=1에서 f(n)>=c*g(n)을 양의 정수 K=1일때 n>=k일때 f(n)>=c*g(n)을 만족시키므로 f(n)=Ω(g(n))을 만족시킨다.



f(n)<=i*g(n)도 증명해야한다.




f(n)|i*g(n)|f(n)<=i*g(n)이고 n>=k을 만족하는 양의 정수 k를 가질때이것의 진위 T/F
---|---|---|
2n^2|1*n^2|F
2n^2|2*n^2|F
2n^2|3*n^2|T

![image](https://user-images.githubusercontent.com/100903674/158025315-968d0304-3c7c-4216-914e-260b6f2b129a.png)

위의 그래프를 보면 양의 정수 c=3에서 f(n)<=ㅑ*g(n)을 양의 정수 K=1일때 n>=k일때 f(n)<=i*g(n)을 만족시키므로 f(n)=Θ(g(n))을 만족시킨다

