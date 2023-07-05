import sys
input = sys.stdin.readline
############################################
container = []
box_info = [0]
############################################
def init(*data):
    global container, box_info
    n = data[0]
    m = data[1]

    box = data[2:]

    # 크기, 맨 앞, 맨 뒤를 저장
    container = [[0, None, None] for _ in range(n + 1)]

    for i in range(m):
        # 자신의 번호와 앞의 박스, 뒤의 박스를 ㅈ장
        box_info.append([i+1, None, None])
        # 맨 앞이 비었다면 맨 앞과, 맨 뒤를 자신으로 저장
        if container[box[i]][1] is None:
            container[box[i]][1] = box_info[-1][0]
            container[box[i]][2] = box_info[-1][0]
            container[box[i]][0] += 1
            continue

        # 앞의 박스는 컨테이너 박스에 있는 맨 뒤의 박스
        box_info[-1][1] = container[box[i]][2]
        # 컨테이너 맨 뒤의 박스는 지금 박스로 갱신
        box_info[container[box[i]][2]][2] = box_info[-1][0]
        container[box[i]][2] = box_info[-1][0]
        container[box[i]][0] += 1


############################################
def move(*data):
    m_src = data[0]
    m_dst = data[1]

    # 옮길 박스 없으면 크기만 출력 후 리턴
    if container[m_src][0] == 0:
        print(container[m_dst][0])
        return

    # 옮겨야하는 장소에 박스 없으면 그대로 옮기고 크기 출력 후 리턴
    if container[m_dst][0] == 0:
        container[m_dst] = container[m_src].copy()
        container[m_src] = [0, None, None]
        print(container[m_dst][0])
        return

    # 일단 dst의 박스를 전부 src로 옮긴 뒤 그다음 전체를 옮겨준다
    # 박스 개수 옮기기
    container[m_src][0] += container[m_dst][0]
    # src의 꼬리 박스에 다음 박스 번호(dst의 맨 앞 박스) 적기
    box_info[container[m_dst][1]][1] = container[m_src][2]
    box_info[container[m_src][2]][2] = container[m_dst][1]
    # src의 꼬리 박스를 dst의 꼬리 박스로 바꾸기
    container[m_src][2] = container[m_dst][2]
    # 전부 옮기고 src 비우기
    container[m_dst] = container[m_src].copy()
    container[m_src] = [0, None, None]
    # 크기 출력
    print(container[m_dst][0])
    return


############################################
def move_front(*data):
    m_src = data[0]
    m_dst = data[1]

    # 둘다 빈 컨테이너 면 0 출력 후 리턴
    if container[m_src][0] == 0 and container[m_dst][0] == 0:
        print(0)
        return

    # src가 비었다면
    if container[m_src][0] == 0:
        # 개수 추가
        container[m_src][0] += 1
        # 맨앞과 맨 뒤는 dst의 맨앞
        container[m_src][1] = container[m_dst][1]
        container[m_src][2] = container[m_dst][1]
        # dst개수 감소
        container[m_dst][0] -= 1
        # dst의 맨 앞은 src맨 앞 박스의 다음 박스
        container[m_dst][1] = box_info[container[m_src][1]][2]
        if container[m_dst][0] == 0:
            container[m_dst][2] = None
        else:
            box_info[container[m_dst][1]][1] = None
        # dst의 맨 앞 박스는 이전 박스 없음
        box_info[container[m_src][1]][2] = None
        # 크기 출력 후 리턴
        print(container[m_dst][0])
        return

    # 반대로 dst가 비었을 경우 위와 동일
    if container[m_dst][0] == 0:
        container[m_dst][0] += 1
        container[m_dst][1] = container[m_src][1]
        container[m_dst][2] = container[m_src][1]
        container[m_src][0] -= 1
        container[m_src][1] = box_info[container[m_dst][1]][2]
        if container[m_src][0] == 0:
            container[m_src][2] = None
        else:
            box_info[container[m_src][1]][1] = None
        box_info[container[m_dst][1]][2] = None
        print(container[m_dst][0])
        return

    # 각 컨테이너 맨 앞의 다음 박스를 서로 바꿔 줌
    if container[m_dst][0] != 1:
        box_info[box_info[container[m_dst][1]][2]][1] = container[m_src][1]

    if container[m_src][0] != 1:
        box_info[box_info[container[m_src][1]][2]][1] = container[m_dst][1]
    box_info[container[m_dst][1]][2], box_info[container[m_src][1]][2] = box_info[container[m_src][1]][2], box_info[container[m_dst][1]][2]
    # 그 다음 각각의 맨 앞을 서로 바꿔 줌
    container[m_dst][1], container[m_src][1] = container[m_src][1], container[m_dst][1]

    if container[m_dst][0] == 1:
        container[m_dst][2] = container[m_dst][1]

    if container[m_src][0] == 1:
        container[m_src][2] = container[m_src][1]
    print(container[m_dst][0])
    return

############################################
def divide_box(*data):
    m_src = data[0]
    m_dst = data[1]

    if container[m_src][0] <= 1:
        print(container[m_dst][0])
        return

    need_count = container[m_src][0] // 2
    temp = [need_count + container[m_dst][0], container[m_src][1], container[m_dst][2]]
    container[m_src][0] -= need_count

    count = 1
    # 0. 중간점을 찾아야 한다.
    box_num = container[m_src][1]
    while True:
        if count == need_count:
            break
        box_num = box_info[box_num][2]
        count += 1

    # 1. m_src의 헤드 박스를 중간점 다음 박스로 바꿈
    container[m_src][1] = box_info[box_num][2]

    # 3. 중간 박스의 다음 박스를 m_dst의 헤드로 바꿔줌
    box_info[box_num][2] = container[m_dst][1]
    # 4. m_dst의 헤드박스였던 친구의 이전 박스를 중간 박스로 바꿔줌
    if container[m_dst][0] == 0:
        temp[2] = box_num
    else:
        box_info[container[m_dst][1]][1] = box_num

    box_info[container[m_src][1]][1] = None
    container[m_dst] = temp.copy()

    print(container[m_dst][0])
    return


############################################
def get_info(*data):
    p_num = data[0]

    a = box_info[p_num][1] if box_info[p_num][1] else -1
    b = box_info[p_num][2] if box_info[p_num][2] else -1

    print(a + (b * 2))
    return


############################################
def get_belt_info(*data):
    b_num = data[0]
    a = container[b_num][1] if container[b_num][1] else -1
    b = container[b_num][2] if container[b_num][2] else -1
    c = container[b_num][0]

    print(a + 2*b + 3*c)
    return


############################################
N = int(input())

fun = {
    100: init,
    200: move,
    300: move_front,
    400: divide_box,
    500: get_info,
    600: get_belt_info
}

for i in range(N):
    order, *data = map(int, input().split())
    fun[order](*data)

# for i in container:
#     print(i)
#
# print(box_info)

