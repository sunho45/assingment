# 분할정복

## 합병정렬 
* 합병정렬의 정의

입력이 2개의 부분리스트로 분할 되고, 부분리스트의 크기가 1/2로 감소하는 분할 정복 알고리즘이다. n개의 숫자를 n/2개의 부분리스트를 분할하고,각각의 부분리스트를 재귀적으로 합병한 후 2개의 정렬된 부분을 합병하는 정렬 

* 합병정렬의 진행과정

Step1. 분할: 배열을 반으로 분할한다. 분할한 배열의 원소는 각각 n/2이다.

Step2. 정렬: 분할한 배열을 각각 따로 정렬한다. 분할한 배열에 원소의 크기가 2개 이상이면 순환 호출을 이용하여 다시 분할 정복 알고리즘을 적용한다.

Step3. 결합: 정렬된 부분 배열들을 하나의 배열로 합병하여 정렬한다.

ex)
하나의 리스트가 주어져있다.
5|13|8|19|21|17|32|30
---|---|---|---|---|---|---|---|

두개의 부분리스트로 분

5|13|8|19| |21|17|32|30 
---|---|---|---|---|---|---|---|---|

두개의 부분리스트들이 분열되어 4개의 부분리스트로 분할되었다
5|13| |8|19| |21|17| |32|30 
---|---|---|---|---|---|---|---|---|---|---|                                                                                     

분할이 끝났다. 
 
5| |13| |8| |19| |21| |17| |32| |30 
---|---|---|---|---|---|---|---|---|---|---|---|---|---|---| 

이제는 정렬과 결합을 할 차례이다.

각각의 하나의 원소들이 왼쪽부터 차례대로 두개씩 정렬되고 결합된다.
5|13| |8|19| |17|21| |30|32
---|---|---|---|---|---|---|---|---|---|---|  

두개의 원소를 가진 부분리스트들이 4개의 원소를 가진 부분리스트들로 정렬되고 결합한다.

 5|8|13|19| |17|21|30|32 
---|---|---|---|---|---|---|---|---|

최종적으로 정렬된 하나의 부분리스트가 만들어진다.

5|8|13|17|19|21|30|32
---|---|---|---|---|---|---|---|
---


---

## 퀵 정렬

* 퀵정렬의 정의

하나의 리스트를 피벗(pivot)을 기준으로 두 개의 부분리스트로 나누어 하나는 피벗보다 작은 값들의 부분리스트, 다른 하나는 피벗보다 큰 값들의 부분리스트로 정렬한 다음, 각 부분리스트에 대해 다시 위 처럼 재귀적으로 수행하는 정렬


* 퀵정렬의 과정

퀵 정렬은 어느 값을 pivot으로 정하는지에 따라 달라진다. 이번은 퀵 정렬중 중요한 함수인 **partiton 함수**를 사용한다.
ex)
다음과 같이 리스트가 주어졌다
12|5|16|3|7|4|10
---|---|---|---|---|---|---|

전체 원소에서 첫번째 값인 12를 피벗으로 정한다.

12|5|16|3|7|4|10
---|---|---|---|---|---|---|
p|                         | 

왼쪽부터 시작하여 5보다 큰 원소인 16을 찾고 오른쪽부터 12보다 작은 원소인 10을 찾는다. 10<16이므로 교환

12|5|10|3|7|4|16
---|---|---|---|---|---|---|
p|                         | 

3부터 시작하여 12보다 큰원소인 16을 찾는다 . 4부터 시작해서 12보다 작은 원소인 4를 찾는다. 더이상 비교할 원소가 없으므로 피벗보다 크거나 같은 원소의 집합과 작거나 캍은 원소의 집합으로 분리될 수 있다. 12와 4를 교환해준다.

4|5|10|3|7|12|16
---|---|---|---|---|---|---|
smaller|smaller|smaller|smaller|smaller|   |bigger|                          

작은 원소의 집합중 가장 첫번째 원소인 4를 피벗으로 한다.

4|5|10|3|7|12|16
---|---|---|---|---|---|---|
p|                         | 

집합에서 피벗을 제외한 왼쪽부터 시작하여 피벗보다 큰 값 5을 찾고 오른쪽부터 시작하여 피벗보다 작은 수3을 찾는다. 5와 3을 교환한다.

4|3|10|5|7|12|16
---|---|---|---|---|---|---|
p|                         |

집합에서 피벗을 제외한 왼쪽부터 시작하여 피벗보다 큰 값 5을 찾고 오른쪽부터 시작하여 피벗보다 작은 수3을 찾는다. 5와 3을 교환한다.
더이상 비교할 원소들이 없으므로 피벗보다 큰 원소의 집합 피벗보다 작은 원소의 집합으로 나눌 수 있다. 4와 3을 교환해준다

3|4|10|5|7|12|16
---|---|---|---|---|---|---|
smaller|  |bigger   |bigger   |bigger   |bigger   |bigger                       |

큰 원소의 집합중 가장 첫번쨰원소인 10을 피벗으로 삼는다

3|4|10|5|7|12|16
---|---|---|---|---|---|---|
 |                         | | p |

큰 원소의 집합에서 5부터 시작하여 10보다 큰 원소인 12를 찾고 16부터 시작하여 작은 원소인 7을 찾는다.
더이상 비교될 원소가 없으므로 피벗보다 작은 원소의 집합과 큰 원소의 집합으로 나눌 수 있다. 7과 10을 바꿔준다


3|4|7|5|10|12|16
---|---|---|---|---|---|---|
sorted| sorted |smaller   |smaller   |   |bigger   |bigger         

정렬되지 않은 작은 원소의 집합중 첫번쨰 값인 7을 피벗으로 잡는다.
3|4|7|5|10|12|16
---|---|---|---|---|---|---|
 |                         | | p |

5부터 시작하여 7보다 큰 값인 10이 다른 집합에 있고 5부터 시작하여 작은 값인 5를 찾았으므로 더이상 비교가 불가능므로 피벗보다 작거나 큰 집합을 나눌 수 있다.

7과 5를 교환한다.

3|4|5|7|10|12|16
---|---|---|---|---|---|---|

7개의 원소에 대한 정렬이 완료되었다.

## 선택 문제 알고리즘
입력값들중 k번째로 크거나 작은  원소를 찾는 알고리즘이다.

히나의 값을 무작위로 피벗으로 정한뒤 피벗보다 크거나 작은 원소의 집합으로 나누어 탐색의 범위를 좁혀 더욱 탐색을 쉽게한다.

* 선택 문제 알고리즘의 과정
다음과 같이 리스트가 주어지고 두번쨰로 작은 원소를 구한다.

1 |10| 5| 8| 7| 6| 4| 3| 2| 9
---|---|---|---|---|---|---|---|---|---|


4를  무작위로 pivot으로 설정한다. 

1 |10| 5| 8| 7| 6| 4| 3| 2| 9
---|---|---|---|---|---|---|---|---|---|
|  |   |   |   |   |   |pivot|


pivot인 4를 기준으로 작은 원소의 집합과 큰 원소의 집합으로 나눈다.

1 |3| 2| 4| 7| 6| 8| 10| 5| 9
---|---|---|---|---|---|---|---|---|---|
|smaller|smaller|smaller|   |bigger   |bigger|bigger|bigger |bigger|bigger|bigger

작은 원소의 집합의 개수를 a라 하고 pivot의 개수를 m이라 할때 
k<a라면 작은 원소의 집합에서
a+m<k라면 큰 원소의 집합에서
k번째 값이 작은 원소의 집합에도 큰 원소의 집합에도 없다면 pivot값이 k번째 작은 값이다.

a=3
k=2
k<a 이므로 
k번째 작은 값은 작은 원소의 집합에 있다.

기존의 큰 원소의 집합과 pivot은 무시해준다.



