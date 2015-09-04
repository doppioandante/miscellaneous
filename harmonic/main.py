import time
import sdl2.ext
import sdl2

class Simulator:
    # PARAMETERS ARE HERE
    m1 = 100.0  # mass of the first body in kg
    m2 = 600.0  # mass of the second body
    k  = 10 # elastic constant of the spring
    d  = 80.0    # initial distance between the two bodies (meter)

    v2 = +19.5   # initial velocity of the second body
    v1 = 0.5    # initial velocity of the first body

    current_t = 0
    points = []

    def get_x_g(self):
        return (self.m1 * self.x1 + self.m2 * self.x2) / (self.m1 + self.m2)

    def __init__(self, width, height):
        self.a1 = 0.0
        self.a2 = 0.0
        self.x1 = -self.d/2
        self.x2 = self.d/2

        self.origin_x = width/2
        self.origin_y = height/2

    def advance(self, dt):
        # Gravity is absent; the only force present in the system is that of
        # the spring, applied to m1 and m2
        self.v1 += self.a1 * dt
        self.x1 += self.v1 * dt
        self.v2 += self.a2 * dt
        self.x2 += self.v2 * dt

        dx = (self.x2 - self.x1) - self.d
        if dx < -self.d:
            exit('''Sorry, the two bodies crashed against each other
                     Adjust your parameters''')
        F1 = 2 * self.k * dx
        F2 = -F1

        self.a1 = F1 / self.m1
        self.a2 = F2 / self.m2

    def tick(self, period, dt):
        t = 0
        while t < period:
            self.advance(dt)
            t += dt

        self.current_t += period

    def draw(self, surface):
        objColor = sdl2.ext.Color(150, 30, 0)
        area1 = (self.origin_x + self.x1 - 10, self.origin_y + 120, 20, 20)
        area2 = (self.origin_x + self.x2 - 10, self.origin_y + 120, 20, 20)
        sdl2.ext.fill(surface, objColor, area1)
        sdl2.ext.fill(surface, objColor, area2)

        dx = (self.x2 - self.x1) - self.d
        spring_color = sdl2.ext.Color(30, min(255, 110*(1 - dx/self.d)), 20)

        spring_area = (area1[0]+area1[2], area1[1]+7, area2[0]-area1[0]-area1[3], 6)
        sdl2.ext.fill(surface, spring_color , spring_area)

        # don't look at me
        graph_y = 270
        graph_x = 10

        size = 4
        delta_t = 10 # pixels
        dot_area = (graph_x + self.current_t*delta_t,
                    max(size, graph_y - abs(self.get_x_g()*2*(graph_y/650))),
                    size,
                    size)
        self.points.append(dot_area)
        for p in self.points:
            sdl2.ext.fill(surface, sdl2.ext.Color(3, 90, 170), p)



sdl2.ext.init()

window = sdl2.ext.Window('Spring Motion', size=(1300, 480))
window.show()
running = True
sim = Simulator(1300, 480)
while running:
    events = sdl2.ext.get_events()
    for event in events:
        if event.type == sdl2.SDL_QUIT:
            running = False
            break
    sdl2.ext.fill(window.get_surface(), color=sdl2.ext.Color(0, 0, 0))
    sim.draw(window.get_surface())
    window.refresh()

    sim.tick(1, 0.001)
    time.sleep(1)

sdl2.ext.quit()
