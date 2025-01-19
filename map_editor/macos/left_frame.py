from tkmacosx import Button
from tkinter import messagebox
import tkinter as tk

class LeftFrame:

    def __init__(self, main_frame, app):
        self.main_frame = main_frame
        self.app = app
        self.left_frame = tk.Frame(self.main_frame, width=200, bg="lightgray")
        self.left_frame.pack(side=tk.LEFT, fill=tk.Y)

        tk.Label(self.left_frame, text="Object Types", bg="lightgray", font=("Arial", 14, "bold")).pack(pady=10)

        self.mob_button = Button(
            self.left_frame,
            text="Mobs",
            command=lambda: self.toggle_frame(self.app.rightframe.mobs_frame),
            bg="#4CAF50",
            fg="white",
            font=("Helvetica", 14, "bold"),
            borderless=True,
        )
        self.mob_button.pack(padx=20, pady=5)

        self.block_button = Button(
            self.left_frame,
            text="Blocks",
            command=lambda: self.toggle_frame(self.app.rightframe.blocks_frame),
            bg="#2196F3",
            fg="white",
            font=("Helvetica", 14, "bold"),
            borderless=True,
        )
        self.block_button.pack(padx=20, pady=5)

        tk.Label(self.left_frame, text="Grid Width (X):", bg="lightgray", font=("Arial", 12)).pack(pady=5)
        self.grid_width_entry = tk.Entry(self.left_frame, font=("Arial", 12))
        self.grid_width_entry.insert(0, "30")
        self.grid_width_entry.pack(padx=10, pady=5)

        tk.Label(self.left_frame, text="Grid Height (Y):", bg="lightgray", font=("Arial", 12)).pack(pady=5)
        self.grid_height_entry = tk.Entry(self.left_frame, font=("Arial", 12))
        self.grid_height_entry.insert(0, "12")
        self.grid_height_entry.pack(padx=10, pady=5)

        apply_button = Button(
            self.left_frame,
            text="Apply",
            command=self.apply_grid_size,
            bg="#FF9800",
            fg="white",
            font=("Helvetica", 12, "bold"),
            borderless=True,
        )
        apply_button.pack(pady=10)

    def toggle_frame(self, frame):
        if frame.winfo_ismapped():
            frame.pack_forget()
        else:
            frame.pack(side=tk.RIGHT, fill=tk.Y)

    def apply_grid_size(self):
        try:
            new_width = int(self.grid_width_entry.get())
            new_height = int(self.grid_height_entry.get())
            if new_width <= 0 or new_height <= 0:
                messagebox.showerror("Error", "Grid dimensions must be greater than 0!")
                return

            map_data = self.app.toolbar.create_map().splitlines()
            self.app.grid_manager.width = new_width
            self.app.grid_manager.height = new_height
            self.app.grid_manager.offset_x = 0
            self.app.grid_manager.offset_y = 0
            self.app.grid_manager.scale = 1
            self.app.grid_manager.canvas.delete("all")
            self.app.grid_manager.draw_grid(new_width, new_height)
            self.app.grid_manager.map_data = {}
            self.app.toolbar.load_map(map_data)
        except ValueError:
            messagebox.showerror("Error", "Please enter valid integers for the grid dimensions!")