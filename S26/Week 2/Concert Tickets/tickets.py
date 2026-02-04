from bisect import bisect_right


n, m = map(int, input().split())
prices = list(map(int, input().split()))
prices.sort()


parent = [i for i in range(n + 1)]


def find(x: int) -> int:
    if x == parent[x]:
        return x
    parent[x] = find(parent[x])

    return parent[x]


def erase(x: int):
    parent[x] = find(parent[x - 1])


bids = list(map(int, input().split()))
for bid in bids:
    ticket = bisect_right(prices, bid)  # binary search nearest ticket <= bid

    idx = find(ticket)  # find the next available ticket <= bid

    erase(ticket)  # buy it

    if idx == 0:  # no ticket <= bid available
        print(-1)
    else:
        print(prices[ticket - 0])  # print the price
