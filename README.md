# DNSFlip

Hey there! 👋

**DNSFlip** is a handy little tool that takes the hassle out of changing your system’s DNS settings. Instead of digging through Windows menus, just fire up DNSFlip, pick what you want from the simple menu, and voilà — your DNS is switched instantly!

## What can DNSFlip do?
- Quickly connect to your favorite DNS service (like OpenDNS, Google, Cloudflare, and more)  
- Manage your own list of DNS IPs — add new ones, edit, delete, or pick which one is active  
- Choose which network interface you want to apply DNS settings to (Wi-Fi, Ethernet, etc.)  
- Reset everything back to automatic with just one click

## How to use it?
1. Run **DNSFlip.exe** as an administrator (important, otherwise it can’t change your DNS)  
2. You’ll see a menu like this:
```markdown
=== DNSFlip ===
1. Connect DNS (OpenDNS)
2. Manage DNS IPs
3. Manage Network Interface (Wi-Fi)
4. Reset to Automatic DNS
0. Exit
Choice:
```

3. Pick your choice by typing the number and pressing Enter 
4. Explore the menus, add your DNS profiles, and switch easily!


## Why run as admin?
Because DNS settings affect your whole system, Windows needs you to have administrator rights to make changes. So remember: right-click and choose **Run as administrator**!


## Wanna download the executable?
Check out the [Releases](https://github.com/ArashMaghsoodi/DNSFlip/releases) page to grab the latest ready-to-run version.

## How to build it yourself
If you want to compile the project from source, here’s a quick way:

```bash
g++ -Wall -Wextra -g3 *.cpp -o DNSFlip.exe
```
(For best results, compile on Windows with a C++17 compiler)

## Got ideas or found a bug?
Feel free to open an issue or send a pull request! I’m happy to hear from you and improve DNSFlip.

Thanks for checking out DNSFlip!
Happy flipping! 🎉