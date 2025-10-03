import random
computer_number = random.randint(1,30)
life = 10
count = 10 -life


while life > 0 :
    print("1부터 30사이의 숫자중 컴퓨터가 정한 숫자를 맞춰보세여")
    print(f"기회는 {life}번 입니다")
    user_input =input("숫자를 입력하시요:")

    try:
        user_num = int(user_input)
    except ValueError:
        print("잘못된 값을 입력했습니다")
        continue

    if user_num < computer_number:
        print("up!")
        life -= 1
        print(f"기회는 {life}번 남았습니다")
    elif user_num > computer_number:
        print("down!")
        life -= 1
        print(f"기회는 {life}번 남았습니다")
    
    else:
        print(f"축하드립니다! 정답입니다! \n대단해요! {count}번 만에 성공하셨어요~ ")

