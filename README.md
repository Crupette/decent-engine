# Decent Engine

A basic framework for most of my (future) projects. Refined over a month of almost continuous development and documentation. Will be worked on as new features are added.

## Getting Started

You need build-essentials and make. You also need libglew-dev, libsdl2-dev, libsdl2-ttf-dev, and liblgm-dev

### Debian
```
$apt install build-essential libglew-dev libsdl2-dev libsdl2-ttf-dev libglm-dev
```

## Building

Just run the make file with 'build' as an argument. The engine binary will be placed in the /bin/ folder

```
make build
```

## Using the engine

To link the engine, add -L [Engine] to the compiler flags, and add the headers to your include directory, replacing [Engine] with the path and name of the compiled binary.

All of the methods are put in the 'DecentEngine' namespace.

To create a window, you must first create an object that inherits from 'DecentEngine::Screen' and contains the init, update, and render functions.

Then you must call DecentEngine::Base::addScreen with a new instance of the screen object.

Finally, you must call DecentEngine::Base::init with the window name, coordinates, dimensions, and flags.

## License

The project is licensed under the GNU General Public License v3.0. see [LICENSE](LICENSE) for more details
