import tkinter as tk
from PIL import Image, ImageTk

class GridManager:

    def __init__(self, main_frame, app):
        self.main_frame = main_frame
        self.app = app
        self.is_dragging = False
        self.offset_x = 0
        self.offset_y = 0
        self.scale = 1
        self.width = 30
        self.height = 12
        self.scale_factor = 1
        self.map_data = {}
        self.images = {}

        self.canvas = tk.Canvas(self.main_frame, bg="white")
        self.canvas.pack(side=tk.LEFT, fill=tk.BOTH, expand=True)

        self.draw_grid()

        self.canvas.bind("<MouseWheel>", self.zoom)
        self.canvas.bind("<Button-1>", self.app.toolbar.handle_left_click)
        self.canvas.bind("<Button-2>", self.start_drag)
        self.canvas.bind("<B2-Motion>", self.drag_view)
        self.canvas.bind("<ButtonRelease-2>", self.stop_drag)

    def delete_item_from_grid(self, event):
        col = int((event.x - self.offset_x) / (self.grid_size * self.scale))
        row = int((event.y - self.offset_y) / (self.grid_size * self.scale))

        if (row, col) in self.map_data:
            self.canvas.delete(self.map_data[(row, col)]["id"])
            del self.map_data[(row, col)]

    def draw_grid(self, width=30, height=12):
        self.grid_size = 50
        self.width = width
        self.height = height
        for x in range(0, width * 50, self.grid_size):
            self.canvas.create_line(x, 0, x, height * 50, fill="gray", dash=(2, 2))
        for y in range(0, height * 50, self.grid_size):
            self.canvas.create_line(0, y, width * 50, y, fill="gray", dash=(2, 2))

    def load_image(self, item):
        if item not in self.images:
            try:
                img = Image.open(f"../images/{item.lower()}.png")
                img = img.resize((self.grid_size, self.grid_size))
                self.images[item] = ImageTk.PhotoImage(img)
            except FileNotFoundError:
                self.images[item] = None
        return self.images[item]

    def place_item_on_grid(self, event):
        if self.app.rightframe.selected_item:
            col = int((event.x - self.offset_x) / (self.grid_size * self.scale))
            row = int((event.y - self.offset_y) / (self.grid_size * self.scale))
            x = col * self.grid_size * self.scale + self.offset_x
            y = row * self.grid_size * self.scale + self.offset_y

            if (row, col) in self.map_data:
                self.canvas.delete(self.map_data[(row, col)]["id"])

            image = self.load_image(self.app.rightframe.selected_item)
            if image:
                item_id = self.canvas.create_image(x, y, anchor=tk.NW, image=image)
                self.map_data[(row, col)] = {"item": self.app.rightframe.selected_item, "id": item_id, "image": image}
                self.update_images()

    def zoom(self, event):
        if event.delta > 0:
            self.scale_factor = 1.1
        else:
            self.scale_factor = 0.9
        self.scale *= self.scale_factor
        self.canvas.scale("all", event.x, event.y, self.scale_factor, self.scale_factor)
        self.offset_x = (self.offset_x - event.x) * self.scale_factor + event.x
        self.offset_y = (self.offset_y - event.y) * self.scale_factor + event.y
        self.update_images()

    def update_images(self):
        for (row, col), data in self.map_data.items():
            image = self.load_image(data["item"])
            if image:
                x = col * self.grid_size * self.scale + self.offset_x
                y = row * self.grid_size * self.scale + self.offset_y
                new_grid_size = int(self.grid_size * self.scale)
                img_resized = Image.open(f"../images/{data['item'].lower()}.png")
                img_resized = img_resized.resize((new_grid_size, new_grid_size), Image.Resampling.LANCZOS)
                image_resized = ImageTk.PhotoImage(img_resized)
                self.canvas.itemconfig(data["id"], image=image_resized)
                self.map_data[(row, col)]["image"] = image_resized
                self.canvas.coords(data["id"], x, y)

    def start_drag(self, event):
        self.is_dragging = True
        self.prev_x = event.x
        self.prev_y = event.y

    def drag_view(self, event):
        if self.is_dragging:
            dx = event.x - self.prev_x
            dy = event.y - self.prev_y
            self.offset_x += dx
            self.offset_y += dy
            self.canvas.move("all", dx, dy)
            self.prev_x = event.x
            self.prev_y = event.y

    def stop_drag(self, event):
        self.is_dragging = False