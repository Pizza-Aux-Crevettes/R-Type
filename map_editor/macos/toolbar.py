from tkmacosx import Button
import tkinter as tk
from tkinter import filedialog, messagebox
from resources import saveData, loadData

class ToolBar:

    def __init__(self, main_frame, root, app):
        self.main_frame = main_frame
        self.app = app
        self.delete_mode = False
        self.toolbar = tk.Frame(self.main_frame, bg="lightgray", height=40)
        self.toolbar.pack(side=tk.TOP, fill=tk.X)
        
        import_button = Button(
            self.toolbar,
            text="Import",
            command=lambda: self.import_map(),
            bg="#2196F3",
            fg="white",
            font=("Helvetica", 12, "bold"),
            borderless=True,
        )
        import_button.pack(side=tk.LEFT, padx=5, pady=5)

        save_button = Button(
            self.toolbar,
            text="Save",
            command=lambda: self.save_map(),
            bg="#4CAF50",
            fg="white",
            font=("Helvetica", 12, "bold"),
            borderless=True,
        )
        save_button.pack(side=tk.LEFT, padx=5, pady=5)

        delete_button = Button(
            self.toolbar,
            text="Delete Mode",
            command=lambda: self.toggle_delete_mode(),
            bg="#b31217",
            fg="white",
            font=("Helvetica", 12, "bold"),
            borderless=True,
        )
        delete_button.pack(side=tk.LEFT, padx=5, pady=5)

        exit_button = Button(
            self.toolbar,
            text="Quit",
            command=root.quit,
            bg="#F44336",
            fg="white",
            font=("Helvetica", 12, "bold"),
            borderless=True,
        )
        exit_button.pack(side=tk.RIGHT, padx=5, pady=5)

    def handle_left_click(self, event):
        if self.app.toolbar.delete_mode:
            self.app.grid_manager.delete_item_from_grid(event)
        else:
            self.app.grid_manager.place_item_on_grid(event)

    def toggle_delete_mode(self):
        self.delete_mode = not self.delete_mode
        mode = "enabled" if self.delete_mode else "disabled"
        messagebox.showinfo("Delete Mode", f"Delete mode {mode}.")

    def create_map(self):
        map = ""
        for y in range(self.app.grid_manager.height):
            for x in range(self.app.grid_manager.width):
                if (y, x) in self.app.grid_manager.map_data:
                    item = self.app.grid_manager.map_data[(y, x)]["item"]
                    map += saveData[item]
                else:
                    map += saveData["Empty"]
            map += "\n"
        return map

    def save_map(self):
        file_path = filedialog.asksaveasfilename(defaultextension=".map", filetypes=[("MAP files", "*.map")])
        file_path = file_path if file_path.endswith(".map") else file_path + ".map"
        file_name = file_path.split("/")[-1]
        file_name = file_name.split(".")[0]
        if file_path:
            with open(file_path, 'w') as file:
                file.write("name=" + file_name + "\n"
                + "map=###\n")
                file.write(self.create_map())
                file.write("###\n")
            messagebox.showinfo("Map Saved", f"Map saved to {file_path}")

    def load_map(self, map_data):
        for row, line in enumerate(map_data):
            col = 0
            while col < len(line):
                item = line[col:col + 4]
                if item in loadData:
                    x1 = (col // 4) * self.app.grid_manager.grid_size
                    y1 = row * self.app.grid_manager.grid_size
                    image = self.app.grid_manager.load_image(loadData[item])
                    if image:
                        item_id = self.app.grid_manager.canvas.create_image(x1, y1, anchor=tk.NW, image=image)
                    else:
                        item_id = None
                    self.app.grid_manager.map_data[(row, col // 4)] = {"item": loadData[item], "id": item_id, "image": image}
                col += 4

    def import_map(self):
        file_path = filedialog.askopenfilename(filetypes=[("MAP files", "*.map")])
        if file_path:
            with open(file_path, 'r') as file:
                data = file.readlines()
                map_data = data[2:-1]
                self.app.grid_manager.canvas.delete("all")
                self.app.grid_manager.draw_grid()
                self.app.grid_manager.map_data = {}
                self.app.grid_manager.offset_x = 0
                self.app.grid_manager.offset_y = 0
                self.app.grid_manager.scale = 1
                self.app.toolbar.load_map(map_data)