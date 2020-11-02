작성자 : 5팀

20183487 이승찬 (팀장)

20193439 김로하

20193478 박예진
 
# C++ Design Pattern(디자인 패턴)
여러 소프트웨어들의 설계에 있어 자주 발생하는 문제들을 해결할 수 있는 재사용성이 높은 효율적인 방법이다. 어느 상황에 어떤 디자인 패턴을 활용할 지에 따라 효율적으로 프로그램을 작성할 수 있다. 디자인 패턴은 사용 목적에 따라 `생성(Creation)`, `구조(Structural)`, `행위 (Behavioral)` 3가지로 나뉜다.

## 1. 생성
객체의 생성에 관여. 캡슐화의 특성을 이용하여 프로그램 구조에 크게 영향이 가지 않도록 한다. 

**1) 추상팩토리(Abstract Factory)** : 서로 연관 되어 있는 객체들을 모아서 클래스를 지정 하지 않아도 상위 팩토리를 통하여 생성이 가능한 패턴이다.

![추상](https://user-images.githubusercontent.com/63458011/96335360-14dab500-10b3-11eb-87f8-c80e8d082389.PNG)

**2) 빌더(Builder)** : 생성과 표현을 분리하여 동일한 생성 절차를 통해 서로 다른 표현을 간접적으로 생성하는 패턴이다.

![빌더](https://user-images.githubusercontent.com/63458011/96335375-29b74880-10b3-11eb-9534-eab9559a5214.PNG)

**3) 팩토리 메서드(Factory Method)** : 상위 클래스에서가 아닌 하위 클래스에서 객체를 생성하는 패턴이다. 하위 클래스의 상위 클래스에 대한 의존도가 낮아진다.

![팩토리](https://user-images.githubusercontent.com/63458011/96335386-39cf2800-10b3-11eb-9a90-4749349c9181.PNG)

**4) 원형(Prototype)** : 미리 만들어져 있는 원형 인스턴스를 복제해서 새로운 객체를 얻는 패턴이다.

![원형](https://user-images.githubusercontent.com/63458011/96335395-43f12680-10b3-11eb-89b2-565a6543a8da.PNG)

**5) 싱글톤(Singleton)** : 하나의 인스턴스를 생성하여 한번만 메모리를 할당한 후 여러번 호출되어도 새로운 인스턴스를 생성하지 않고 동일한 인스턴스를 사용하는 패턴이다. 

![싱글톤](https://user-images.githubusercontent.com/63458011/96335400-4fdce880-10b3-11eb-9c88-43c10b64dbed.PNG)


 
## 2. 구조
클래스 or 객체의 합성에 관여. 조합하여 더 큰 구조를 만들 수 있다.

**1) 어댑터(Adapter)** : 기존의 클래스 등의 호환성 없는 인터페이스를 다른 클래스에서도 이용 가능하도록 변환하는 패턴이다.

![어댑터](https://user-images.githubusercontent.com/63458011/96335427-74d15b80-10b3-11eb-9d58-60b7011316ca.PNG)

**2) 브리지(Bridge)** : 구현부와 추상부를 독립적으로 변형 가능하게 한다. 기능과 구현의 클래스를 분리하는 방법이다. 상속과 같은 확장 설계에 용이하다.

![브리지](https://user-images.githubusercontent.com/63458011/96335433-7f8bf080-10b3-11eb-9c23-7e4f9c5013fc.PNG)

**3) 컴퍼지트(Composite)** : 객체들을 트리 구조로 구성하여 단일/복합 객체의 관계를 동일하게 다룰 수 있는 패턴이다.

![컴퍼지트](https://user-images.githubusercontent.com/63458011/96335438-89adef00-10b3-11eb-8af3-e990419c8699.PNG)

**4) 데커레이터(Decorator)** : 기능을 확장하기 위해 유연성을 주는 패턴으로 임의의 객체에 기능 추가를 위해 다른 객체를 덧붙인다.

![데커레이터](https://user-images.githubusercontent.com/63458011/96335443-90d4fd00-10b3-11eb-9fb5-c92b33b4706b.PNG)

**5) 퍼사드(Facade)** : 여러 서브 시스템들을 집합해 하나의 인터페이스를 제공하여 서브 시스템 관리가 용이하다.

![퍼사드](https://user-images.githubusercontent.com/63458011/96335445-9a5e6500-10b3-11eb-9178-fa9910f53e98.PNG)

**6) 플라이웨이트(Flyweight)** : 객체가 필요할 때마다 생성하는 것이 아닌 최대한 공유를 함으로써 메모리를 절약한다. 유사 객체들을 적은 메모리로 생성 가능하다.

![플라이웨이트](https://user-images.githubusercontent.com/63458011/96335449-a518fa00-10b3-11eb-900c-3a95d9ac7217.PNG)

**7) 프록시(Proxy)** : 접근이 어려운 객체와 그 객체에 접근하려는 객체 사이의 인터페이스 역할을 한다.

![프록시](https://user-images.githubusercontent.com/63458011/96335452-aea26200-10b3-11eb-89d7-2bfb1c539c59.PNG)

 
## 3. 행위
클래스 or 객체의 상호작용 방법과 책임을 분산하는 법을 정의.

**1) 책임 연쇄(Chain of Responsibility)** : 요청하는 객체가 사건을 처리할 수 있는 객체에게 바로 요청하는 것이 아닌 처리하는 객체들을 순차적으로 묶어서 사건 처리를 요청하면 순차적으로 요청받은 것을 확인하고 처리를 못하면 다음의 처리하는 객체에게 넘겨주어서 처리하는 패턴이다.

![책임연쇄](https://user-images.githubusercontent.com/63458011/96335462-bfeb6e80-10b3-11eb-8194-c9b4267a1a20.PNG)

**2) 커맨드(Command)** : 객체의 행위를 객체화 하여 필요시에 이용할 수 있도록 하는 패턴이다. 요청을 큐(queue)하거나 로그로 기록하거나, 작업취소도 할 수 있다. 

![커맨드](https://user-images.githubusercontent.com/63458011/96335467-ca0d6d00-10b3-11eb-83e2-69600796b51f.PNG)

**3) 해석자(Interpreter)** : 문법 규칙을 클래스화 한 구조로, 일련의 규칙을 정의된 언어를 해석하는 패턴이다. 이 패턴의 장점은  문법의 추가 및 수정, 구현이 쉬워지나 복잡한 문법의 경우 관리 및 유지가 어려워진다는 단점이 있다.

![인터프리터](https://user-images.githubusercontent.com/63458011/96335469-d1347b00-10b3-11eb-8d3c-26339150e3af.PNG)

**4) 반복자(Iterator)** : 무언가 많이 모여있는 것을 하나씩 순차적으로 처리하는 패턴이다. for문에서 많이 쓰는 변수 i의 기능을 추상화하여 일반화 한 것이 반복자 패턴이다.

![이터레이터](https://user-images.githubusercontent.com/63458011/96335480-deea0080-10b3-11eb-93d3-052f49a17596.PNG)

**5) 중재자(Mediator)** : 각각의 객체간의 복잡한 로직을 사용하지 않고, 중재자가 되는 하나의 객체에 로직을 캡슐화하여 위임하여 처리하는 패턴이다. 이는 통신은 객체간 서로 통신을 하지 않으며, 중재자를 통해 객체간의 통신을 할 수 있게된다. 통신하는 객체 간의 의존성을 줄일 수 있고, 유지 보수 및 재사용의 확장성에 유리하다.

![미디에이터](https://user-images.githubusercontent.com/63458011/96335490-f2956700-10b3-11eb-8f5b-47f7ea6f10db.PNG)

**6) 메멘토(Memento)** : Memento는 유품, 기념물이라는 뜻이다. 메멘토 패턴은 객체의 상태를 저장하여 필요에 의해 객체의 상태를 이전으로 되돌리는 패턴이다.
메멘토 패턴에는 3개의 객체가 이용된다. Originator는 객체의 상태값을 가지고 있는 객체이고, 그 상태값을 Memento라는 객체에 저장을 한다. 그리고 CareTaker는 Memento를 관리하는 객체이다. 

![메멘초](https://user-images.githubusercontent.com/63458011/96335499-f9bc7500-10b3-11eb-8680-471579c3b7d5.PNG)

**7) 옵저버(Observer)** : 옵저버(Observer)는 객체의 상태변화를 관찰하는 관찰자로, 어떤 객체의 상태가 변할 때, 해당 객체와 연관이 있는 객체들에게 연락을 하여 내용이 바뀌는 패턴이다.

![옵서버](https://user-images.githubusercontent.com/63458011/96335504-0c36ae80-10b4-11eb-8cef-68695ccbe991.PNG)

**8) 상태(State)** : 객체가 특정 상황에 따라 행동하는 것이 다른 상황일 때, 객체 스스로 자신의 상태를 체크하여 스스로 행동을 변경할수 있게 하는 패턴이다.

![스테이트](https://user-images.githubusercontent.com/63458011/96335507-12c52600-10b4-11eb-8665-1c47f8946ba8.PNG)

**9) 스트래티지(Strategy)** : 객체의 알고리즘을 정의하고 클래스를 통해 캡슐화하여 필요한 알고리즘을 선택해 사용할 수 있게 해주는 패턴이다. 알고리즘을 사용하는 객체와는 독립적으로 변경하거나 구현할 수 있다.

![스트래티지](https://user-images.githubusercontent.com/63458011/96335511-1f497e80-10b4-11eb-8d7a-22cbdd6ef763.PNG)

**10) 템플릿 메소드(Template Method)** : 알고리즘이 단계별로 나누어 질 경우 하위 클래스로 캡슐화해두어 일부분을 수정하거나 변경을 하더라도 전체의 구조는 바꾸지 않는 패턴이다.

![템플릿](https://user-images.githubusercontent.com/63458011/96335516-27092300-10b4-11eb-94ef-f20d3ca2347a.PNG)

**11) 비지터(Visitor)** : 각 데이터 구조에서 처리 기능만 분리하여 별개의 클래스로 생성한다. 분리는 처리 기능은 각 클래스를 방문해가며 기능을 실행한다.

![비지터](https://user-images.githubusercontent.com/63458011/96335520-31c3b800-10b4-11eb-96aa-a549f1f9c4d3.PNG)


### 참고자료
[ref] https://copynull.tistory.com/category/Gof%20Design%20Pattern
