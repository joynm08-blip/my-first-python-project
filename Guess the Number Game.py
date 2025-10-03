import random

computer_number = random.randint(1, 30)
life = 10

print("1부터 30사이의 숫자중 컴퓨터가 정한 숫자를 맞춰보세요!")

while life > 0:
    count = 10-life+1
    print(f"기회는 {life}번 남았습니다.")
    user_input = input("숫자를 입력하세요: ")

    try:
        user_num = int(user_input)
    except ValueError:
        print("잘못된 값을 입력했습니다. 숫자만 입력해주세요!")
        continue

    # 범위를 벗어나는 값에 대한 예외 처리도 추가하면 더 좋습니다!
    if not (1 <= user_num <= 30):
        print("범위를 벗어났습니다. 1부터 30 사이의 숫자를 입력해주세요!")
        continue

    if user_num < computer_number:
        print("Up!")
        life -= 1
    elif user_num > computer_number:
        print("Down!")
        life -= 1
    else:
        # 1. 시도 횟수를 정답을 맞춘 '지금' 계산합니다.
        #    (전체 기회 10 - 남은 기회 life + 1 = 현재 시도 횟수)
        152
        print(f"🎉 축하드립니다! 정답입니다!")
        print(f"대단해요! {count}번 만에 성공하셨어요~")
        
        # 2. 정답을 맞췄으니 break로 게임을 종료합니다.
        break

# life가 0이 되어 while문이 끝났을 경우 (실패한 경우)
if life == 0:
    print(f"아쉽네요, 모든 기회를 사용했습니다. 정답은 {computer_number}였습니다.")