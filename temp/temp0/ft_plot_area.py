# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    ft_plot_area.py                                    :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anmakhov <anmakhov@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/06/08 15:32:16 by anmakhov          #+#    #+#              #
#    Updated: 2026/06/08 15:35:12 by anmakhov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

def ft_plot_area():
    length = int(input("Enter length: "))
    width= int(input("Enter width: "))
    plot = length * width
    print("Plot area: ", plot)
