from tkmacosx import Button
import tkinter as tk
from resources import Characteristic

class RightFrame:

    def __init__(self, main_frame, app):
        self.main_frame = main_frame
        self.app = app
        self.selected_item = None

        self.right_frame = tk.Frame(self.main_frame, width=300, bg="lightgray")
        self.right_frame.pack(side=tk.RIGHT, fill=tk.Y)

        tk.Label(self.right_frame, text="Item Details", bg="lightgray", font=("Arial", 12, "bold")).pack(pady=10)

        self.details_text = tk.Text(self.right_frame, bg="white", width=30, height=40, state=tk.DISABLED)
        self.details_text.pack(padx=10, pady=10)

        self.mobs_frame = tk.Frame(self.main_frame, height=200, bg="lightgray")
        self.display_mobs()
        self.mobs_frame.pack(side=tk.RIGHT, fill=tk.Y)
        self.mobs_frame.pack_forget()

        self.blocks_frame = tk.Frame(self.main_frame, height=200, bg="lightgray")
        self.display_blocks()
        self.blocks_frame.pack(side=tk.RIGHT, fill=tk.Y)
        self.blocks_frame.pack_forget()

    def display_mobs(self):
        tk.Label(self.mobs_frame, text="Mobs", bg="lightgray", font=("Arial", 10, "bold")).pack(pady=5)
        items = ["Mob1", "Mob2", "Mob3", "Mob4", "Boss"]
        for item in items:
            image = self.app.grid_manager.load_image(item)
            if image:
                btn = tk.Label(self.mobs_frame, image=image, bg="lightgray")
                btn.image = image
                btn.bind("<Button-1>", lambda e, i=item: self.select_item(e, i))
                btn.pack(side=tk.TOP, padx=5, pady=5)

    def display_blocks(self):
        tk.Label(self.blocks_frame, text="Blocks", bg="lightgray", font=("Arial", 10, "bold")).pack(pady=5)
        items = ["Block1", "Block2", "Block3", "Block4"]
        for item in items:
            image = self.app.grid_manager.load_image(item)
            if image:
                btn = tk.Label(self.blocks_frame, image=image, bg="lightgray")
                btn.image = image
                btn.bind("<Button-1>", lambda e, i=item: self.select_item(e, i))
                btn.pack(side=tk.TOP, padx=5, pady=5)

    def select_item(self, event, item):
        self.selected_item = item
        self.details_text.config(state=tk.NORMAL, fg="black")
        self.details_text.delete(1.0, tk.END)
        self.details_text.insert(tk.END, f"{Characteristic[item]}\n")
        self.details_text.config(state=tk.DISABLED)