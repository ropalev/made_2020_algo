def bin_search(nums, value):
    if nums[-1] < value:
        return nums[-1]
    elif nums[0] > value:
        return nums[0]
    left = 0
    right = len(nums) - 1
    while left <= right:
        mid = left + (right - left) // 2
        if nums[mid] == value:
            right = mid
            break
        elif nums[mid] >= value:
            right = mid - 1
        else:
            left = mid + 1
    if (right >= 0 & left <= len(nums) - 1):
        if abs(value - nums[left]) < abs(value - nums[right]):
            res = nums[left]
        else:
            res = nums[right]
    return res

if __name__ == "__main__":
    _, _ = [int(i) for i in input().split()]
    lst1 = [int(i) for i in input().split()]
    lst2 = [int(i) for i in input().split()]
    res_lst = []
    for i in lst2:
        res_lst.append(bin_search(lst1, i))
    print(*res_lst, sep="\n")