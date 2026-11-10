/*
 TITAN HAND CAR — conceptual chassis layout
 Units: mm. This is a fit-planning model, not manufacturing-ready.
 Verify all component dimensions and mounting holes first.
*/
$fn = 48;

base_L = 180;
base_W = 120;
base_T = 5;
corner_R = 10;

motor_L = 70;
motor_W = 22;
motor_H = 18;
motor_spacing_from_center = 48;

wheel_D = 65;      // placeholder: measure your actual wheels
wheel_W = 26;      // placeholder
wheel_x = 65;

caster_plate_L = 28;
caster_plate_W = 27;
caster_plate_T = 5;
caster_hole_spacing = 19; // assumed square pattern; verify actual pattern
caster_hole_D = 2.3;      // assumed M2 clearance; verify screw size
caster_y = 42;

module rounded2d(l,w,r) {
  hull() for (x=[-l/2+r,l/2-r])
    for (y=[-w/2+r,w/2-r])
      translate([x,y]) circle(r);
}

module base() {
  color("dimgray")
    linear_extrude(base_T) rounded2d(base_L,base_W,corner_R);
}

module motor_block(x) {
  translate([x,0,base_T+motor_H/2])
    color("gold") cube([motor_W,motor_L,motor_H],center=true);
}

module wheel(x) {
  translate([x,0,wheel_D/2])
    rotate([0,90,0])
      color("black") cylinder(d=wheel_D,h=wheel_W,center=true);
}

module caster_plate() {
  translate([0,caster_y,base_T])
    color("silver")
      difference() {
        linear_extrude(caster_plate_T)
          rounded2d(caster_plate_L,caster_plate_W,2);
        for (x=[-caster_hole_spacing/2,caster_hole_spacing/2])
          for (y=[-caster_hole_spacing/2,caster_hole_spacing/2])
            translate([x,y,-0.1])
              cylinder(d=caster_hole_D,h=caster_plate_T+0.2);
      }
}

module component_envelope(x,y,l,w,h,label) {
  translate([x,y,base_T])
    color(label) cube([l,w,h],center=false);
}

base();

// Motor visual envelopes
motor_block(-motor_spacing_from_center);
motor_block(motor_spacing_from_center);

// Wheel visual envelopes (shaft alignment must be verified)
wheel(-wheel_x);
wheel(wheel_x);

// Caster plate envelope
caster_plate();

// Approximate electronics envelopes — not drilled mounting holes
component_envelope(-62,-38,55,28,8,"forestgreen"); // ESP32 area
component_envelope(15,-48,43,43,12,"firebrick");   // L298N area
component_envelope(-25,-58,65,30,20,"royalblue");  // battery area
component_envelope(-10,48,20,16,5,"purple");       // APDS-9960 area
