# powdbench
AM powder test rig

## Serial protocol
### From MCU to host
- inf = information
- err = error
- par = sd card setting
- sta = machine status
- mov = motor moving
- run = program running
- nru = idle
- mvd = manuel move finished
- pos = motor position

### From host to MCU
- par = reglage a enregister sur la carte sd
- apa = sd card settings query
- str = start program
- stp = stop program
- mov = 1:powder, 2:head, 3:bed
- sta = stati request
- hme = got to 0
- hm1 = powder 0
- hm2 = head 0
- hm3 = bed 0
- pos = motor position query
- sep = set motor position
- rst = MCU reset
- ctn = continue program

### Errors
- SD card init error: err01
- Setting parse error: err02
- Setting write error: err03

### Info
- SD card init successfull: inf01
- Setting parsing successfull: inf02
- Setting write successfull: inf03
- Program started: inf04
- Program stopeed: inf05
- Motors homed: inf06
- Program can continue: inf08

# SD card settings file format
## Each line should only contain a number

- poudre\_step\_mm step/mm
- chariot\_step\_mm step/mm
- lit\_step\_mm step/mm

- poudre\_speed mm/s
- chariot\_speed mm/s
- lit\_speed mm/s

- poudre\_acceleration mm/s²
- chariot\_acceleration mm/s²
- lit\_acceleration mm/s²

- poudre\_position mm
- chariot\_position mm
- lit\_position mm

- multiplicateur\_premieres\_couche int
- nombre de couhe affecté par multiplicateur int
- nombre de couche

- delai entre chaque passe secondes
- delai partout
