# ECS-rules

1. 엔티티를 사용할 때, 객체가 아닌 ID(uint16_t)로 식별한다.
2. 컴포넌트는 데이터만 가져야 한다. (따라서, 구조체로 구현하는게 좋다.)
3. 시스템에는 로직이 포함된다. 엔티티의 ID를 매개변수로 받는다. 엔티티에게 시스템을 구동시킬 컴포넌트가 존재하면 로직을 수행한다.
4. 데이터 지향성, 캐시 친화적인 사고력을 길러야 한다. (로직 한번에 최소 종류의 데이터만 참조하도록 해볼 것.)
5. 기능을 잘게 쪼갤 것.