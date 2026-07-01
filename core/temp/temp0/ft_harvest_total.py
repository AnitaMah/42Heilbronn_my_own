# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    ft_harvest_total.py                                :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anmakhov <anmakhov@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/06/08 15:38:23 by anmakhov          #+#    #+#              #
#    Updated: 2026/06/08 15:38:23 by anmakhov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

def ft_harvest_total():
    harvest1 = int(input("Day 1 harvest: "))
    harvest2 = int(input("Day 2 harvest: "))
    harvest3 = int(input("Day 3 harvest: "))
    print("Total harvest: ", harvest1 + harvest2 + harvest3)
