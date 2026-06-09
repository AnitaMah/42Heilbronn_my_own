# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    ft_garden_security.py                              :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anmakhov <anmakhov@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/06/09 12:49:59 by anmakhov          #+#    #+#              #
#    Updated: 2026/06/09 12:56:46 by anmakhov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

class Plant:
    def __init__(self, name, height, age):
        self.name = name
        self.height = height
        self.age = age

    def set_height(self, new_height: int) -> None:
        if (self.height < 0):
            print("Error, height can't be negative\nHeight update rejected")
        else:
            self.height = new_height
    def set_age(self, new_age: int) -> None:
        if (self.age < 0):
            print("Rose: Error, age can't be negative\nAge update rejected")
        else:
            self.age = new_age

if __name__ == "__main__":
    plant = ("Rose", 12, 5)
    plant.set_height(-5)
    plant.set_age(-2)
    plant.set_height(25)
    plant.set_age(12)
