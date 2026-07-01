# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    ft_plant_age.py                                    :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anmakhov <anmakhov@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/06/08 15:42:52 by anmakhov          #+#    #+#              #
#    Updated: 2026/06/08 15:44:08 by anmakhov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

def ft_plant_age():
    plant_age = int (input("Enter plant age in days: "))
    if (plant_age > 60):
        print("Plant is ready to harvest!")
    else:
        print("Plant needs more time to grow.")
