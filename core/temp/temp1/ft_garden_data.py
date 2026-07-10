# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    ft_garden_data.py                                  :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anmakhov <anmakhov@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/06/08 16:24:52 by anmakhov          #+#    #+#              #
#    Updated: 2026/07/08 12:49:16 by anmakhov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

class Plant:
    def __init__(self, name, height, age):
        self.name = name
        self.height = height
        self.age = age

    def show(self):
        print(f"{self.name}: {self.height}cm, {self.age} days old")

if __name__ == "__main__":
    print("=== Garden Plant Registry ===")
    plant1 = Plant("Peony", 30, 20)
    plant2 = Plant("Lilac", 120, 45)
    plant3 = Plant("Hydrangea", 80, 140)
    plant1.show()
    plant2.show()
    plant3.show()
