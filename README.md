## Dyson Purifier Cool Gen1 IR remote controller decoder

Base pulse width is around 740us, with +/- 185us margin correction.
Total 22 bits used, last two is cycling on each button press (00, 01, 10, 11), replaced with dash.

```
btn    device id? command    cycle
POWER  0001001001 0000001111 --
AUTO   0001001001 1010101000 --
INFO   0001001001 1011010100 --
NIGHT  0001001001 1001001001 --
UP     0001001001 0101010000 --
DOWN   0001001001 0101101001 --
ROTATE 0001001001 0011000000 --
```