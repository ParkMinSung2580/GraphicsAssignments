**1.VBO,VAO,EBO의 역할을 각각 한 문장으로 설명하라.**

VBO(vertex buffer object) - 버텍스 정보를 저장하고 있는 버퍼 객체로 좌표(x,y,z),컬러(r,g,b),UV값(u,v)을 가지고 있다.

VAO(vertex array object) - VBO에 담긴 정점 데이터들을 어떻게 읽어올지 알려주는 역할을 한다.

EBO(element buffer object) - 사용할 수 있고 안사용 할 수 있다(EBO 없이도 도형을 그릴 수 있다.). 정점을 인덱스를 저장하여 중복되는 정점 데이터를 사용을 줄이고 인덱스의 순서에 따라 도형을 그릴 수 있도록 하는 버퍼 객체다.

EBO 내용 참조 : https://blog.everdu.com/313

**2.attribute location 1과 buffer binding index 0은 어떻게 다른가?**







**3.정점 개수와 glDrawElements의 count가 다른 이유는?**





