def ft_count_harvest_recursive():
    days_until_harvest = int(input("Days until harvest: "))
    def helper(day, total):
        if day > total:
            print("Harvest time!")
            return
        print(f"Day {day}")
        helper(day + 1, total)
    helper(1, days_until_harvest)
