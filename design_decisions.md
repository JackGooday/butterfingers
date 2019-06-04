# Design Decisions

## Pivot bearing sizes

To have M3 rods through the entire motor unit, they need to pass around the outside of the motor (minimum width of 42mm) and inside the bearing. A bearing with an internal diameter (ID) of 50mm is to small (leaves 4mm on each side, an M3 rod is 3mm). Need an ID of 55 or larger. The cheapest bearing you can get of this size is \$25, which is too much of a difference from the \$11 30ID one.
50mm ones are cheap, however. If you were to use rods thinner than M3, that might work

## Motor positioning with respect to reference frames

It is important to orient the motors so that their wires don't get tangled when the arm is in action. To do this, we need to minimise the reference frames that the motor wires cross.

We have four main reference frames:

1. Ground frame
2. DOF1 frame, at the pivot head
3. DOF2 frame, on the backing panel
4. DOF3 frame, with the belt on the DOF3 motor

Something simple that we can do is orient the DOF1 motor so that the shaft is fixed with respect to the ground frame. This means that the motor's base (and its wires) are stationary with respect to the DOF1 frame.

We can do this at the other end as well, with the DOF3 motor. Having the DOF3 motor's base fixed in the DOF2 frame (fixed to the backing panel) means its wires have to cross one less frame.

So, we have DOF1 motor wires fixed in DOF1 frame, and DOF3 motor wires fixed in DOF2 frame. These are going to have to meet up! This isn't as much of an issue as it first seems though, because the difference between DOF1 and DOF2 frames is *never more than 180 degrees*, unlike most other frames (the arm can't move through the desk).

All we have to decide now is where we want the electronics; DOF1 frame or DOF2. Because 3 or 4 (depending on orientation of DOF2 motor) of the motors are fixed in DOF2 frame, let's use that. It also has more space.



This transition should happen across DOF2, as this is the only DOF that isn't expected to spin 360 degrees.
