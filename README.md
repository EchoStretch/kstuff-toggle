# Kstuff Toggle

Boost homebrew game performance on your PS5 by disabling Kstuff after launching the game. Requires sending the payload via netcat or using the Homebrew Launcher with the Websrv payload.

---

### ✅ Installation & Launch

1. **Copy kstuff-toggle folder** to:
   - `/data/homebrew/`  
   - `/mnt/usb#/homebrew/` *(replace `#` with your USB number, e.g., `usb0`, `usb1`, etc.)*
   - `/mnt/ext#/homebrew/` *(replace `#` with your EXT number, e.g., `ext0`, `ext1`, etc.)*

2. **Included Payload Files:**:
   - `kstuff-toggle-1.elf` *Just PS5 sysentvec*
   - `kstuff-toggle-2.elf` *Just PS4 sysentvec*
   - `kstuff-toggle-3.elf` *Both sysentvec*
   - `homebrew.js`

3. **Inside kstuff-toggle folder**, rename:
   - `kstuff-toggle.elf` *Rename kstuff-toggle-#.elf to kstuff-toggle.elf*

4. **Install the Homebrew Launcher** and send the Websrv payload to your console:  
   👉 [Websrv v0.26.1](https://github.com/ps5-payload-dev/websrv/releases/tag/v0.23.1)

5. **Open the Homebrew Launcher.**  
   With the USB plugged in, your kstuff-toggle should appear.  
   **Select a kstuff-toggle and run it.**

---

### 📌 Example Folder Structure

`/data/homebrew/kstuff-toggle/`, `/mnt/usb0/homebrew/kstuff-toggle/` or `/mnt/ext0/homebrew/kstuff-toggle/`
   - `kstuff-toggle.elf`
   - `homebrew.js`

---
