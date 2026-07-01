# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    ft_count_harvest_iterative.py                      :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anmakhov <anmakhov@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/06/08 15:53:11 by anmakhov          #+#    #+#              #
#    Updated: 2026/06/08 16:00:28 by anmakhov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

def ft_count_harvest_iterative():
    days_until_harvest = int(input("Days until harvest: "))
    for i in ragne(1, days_until_harvest, days_until_harvest + 1):
        print("Day", i)
    print("Harvest time!")
