import Image from "next/image";

const screenshots = [
  {
    src: "/engineshowcase.png",
    title: "the engine",
    caption:
      "The engine's current state — very early development. Right now only object rendering works... and we managed to make a spinning cube!! 🎉",
    alt: "Current state of the physics engine",
  },
  {
    src: "/neuralnetworkshowcase.png",
    title: "the network",
    caption:
      "The network's current state — learning from scratch, starting with handwritten digits before it ever touches a backflip.",
    alt: "Current state of the neural network",
  },
];

/* one node on the path */
function PathNode({
  label,
  first = false,
}: {
  label: string;
  first?: boolean;
}) {
  return (
    <div className="relative flex flex-col items-center">
      {!first && (
        <span
          aria-hidden
          className="w-px flex-1 bg-gradient-to-b from-transparent via-[#f5c66b]/40 to-[#f5c66b]/40"
        />
      )}
      <span
        aria-hidden
        className="relative z-10 my-2 flex h-5 w-5 items-center justify-center rounded-full border-2 border-[#f5c66b]/70 bg-[#1c1a24]"
      >
        <span className="h-2 w-2 rounded-full bg-[#f5c66b]" />
      </span>
      <span className="mb-2 text-[11px] uppercase tracking-[0.25em] text-[#8f86a8]">
        {label}
      </span>
    </div>
  );
}

export default function Home() {
  return (
    <div className="flex min-h-full flex-col bg-[#1c1a24] text-[#f3eee4]">
      {/* cozy banner */}
      <div className="border-b border-white/10 bg-[#2a2536] px-4 py-3 text-center text-sm text-[#d9cfb8]">
        ✨ This is a{" "}
        <span className="font-semibold text-[#f5c66b]">vibecoded</span> website
        — just a small showcase of how the project works right now. The story is written by me 
        <span className="font-semibold text-[#f5c66b]"> @Bober</span> on slack — not AI trust me😩 .{" "}
        <span className="font-semibold text-[#f5c66b]">
          It is NOT finished!
        </span>{" "}
        ✨
      </div>

      <main className="mx-auto flex w-full max-w-3xl flex-1 flex-col gap-20 px-6 py-16">
        {/* hero */}
        <header className="text-center">
          <p className="mb-2 text-sm uppercase tracking-[0.3em] text-[#8f86a8]">
            Project lore
          </p>
          <h1 className="text-4xl font-bold tracking-tight text-[#f5c66b] sm:text-5xl">
            PhysicsSim - wierd name ikik
          </h1>
          <p className="mx-auto mt-4 max-w-xl text-lg leading-relaxed text-[#cfc6b8]">
            The name says &quot;physics engine&quot;, but its really about {" "}
            <strong className="text-[#f5c66b]">
              Trying to teach AI how to do a backflip.
            </strong>{" "}
            This is the story of how it&apos;s going so far — scroll down the
            path and follow it to the end.
          </p>
        </header>

        {/* the path begins */}
        <div className="relative">
          {/* the long connecting line running through every chapter */}
          <span
            aria-hidden
            className="pointer-events-none absolute top-0 bottom-0 left-1/2 w-px -translate-x-1/2 bg-gradient-to-b from-transparent via-[#f5c66b]/30 to-[#f5c66b]/30"
          />

          {/* chapter 1 */}
          <div className="relative">
            <PathNode label="chapter one — the spark" first />
            <section className="mt-4 rounded-2xl border border-white/10 bg-[#241f30] p-8">
              <h2 className="text-2xl font-semibold text-[#f5c66b]">
                How did I come up with this idea?
              </h2>
              <p className="mt-3 leading-relaxed text-[#cfc6b8]">
                One day, a YouTube video appeared on my main page about
                making an AI learn to do backflip. I decided{" "}
                <strong className="text-[#f3eee4]">
                  not to watch it until I build something like this myself.
                </strong>{" "}
                
                 
              </p>
              <h3 className="text-2xl font-semibold text-[#f5c66b]">
                ??? Why ???
                </h3>
              <p className="mt-3 leading-relaxed text-[#cfc6b8]">
                Well, just bc. Also I&apos;ve never made a physics engine
                before. I always kind of ran away from the idea of properly
                calculating collisions, forces, etc. — it just felt hard for
                me so I instincively avoided it ;D

              </p>
              
              <p className="mt-3 leading-relaxed text-[#cfc6b8]">
                And I&apos;d never made a neural network before either. Even
                better: I decided to do it{" "}
                <strong className="text-[#f3eee4]">from scratch</strong>, so I
                can understand the underlying math.
              </p>
              <p className="mt-3 leading-relaxed text-[#cfc6b8]">
                So the whole project stands on two main pillars:
              </p>
              <div className="mt-4 grid gap-3 sm:grid-cols-2">
                <div className="rounded-xl bg-[#2e2940] p-4 text-center">
                  <p className="font-semibold text-[#f3eee4]">the engine</p>
                  <p className="text-sm text-[#b8ae9d]">
                    physics, collisions, forces — the HARD stuff
                  </p>
                </div>
                <div className="rounded-xl bg-[#2e2940] p-4 text-center">
                  <p className="font-semibold text-[#f3eee4]">
                    the neural network
                  </p>
                  <p className="text-sm text-[#b8ae9d]">
                    trained to make a body inside the engine backflip
                  </p>
                </div>
              </div>
            </section>
          </div>

          {/* chapter 2 */}
          <div className="relative mt-14">
            <PathNode label="chapter two — the network" />
            <section className="mt-4 rounded-2xl border border-white/10 bg-[#241f30] p-8">
              <h2 className="text-2xl font-semibold text-[#f5c66b]">
                About the neural network
              </h2>
              <p className="mt-3 leading-relaxed text-[#cfc6b8]">
                Since I have no previous experience in making ai I started at the classical AI entry point:{" "}
                <strong className="text-[#f3eee4]">the MNIST dataset</strong>{" "}
                (handwritten digits).
              </p>
              <p className="mt-3 leading-relaxed text-[#cfc6b8]">
                So far I&apos;ve managed to implement{" "}
                <strong className="text-[#f3eee4]">
                  working calculus math
                </strong>{" "}
                in Python and a proper NN structure (it is{" "}
                <em>nowhere near</em> optimized xD). Once MNIST works properly{" "}
                <em>and</em> fast (actual matrix operations and not just recursion through python objects 🙏),
                 the network graduates and moves onto my
                in-engine character. That&apos;s the plan. (Hopefully it works out)
              </p>
            </section>
          </div>

          {/* chapter 3 */}
          <div className="relative mt-14">
            <PathNode label="chapter three — the engine" />
            <section className="mt-4 rounded-2xl border border-white/10 bg-[#241f30] p-8">
              <h2 className="text-2xl font-semibold text-[#f5c66b]">
                About the engine
              </h2>
              <p className="mt-3 leading-relaxed text-[#cfc6b8]">
                I had previous experience with C++ and OpenGL - I made a{" "}
                <a href='https://minecraftplus.vercel.app/'><strong className="text-[#f5c66b] underline">Minecraft clone</strong></a> in
                OpenGL and C++ before. But it didn&apos;t include{" "}
                any physics, for obvious reasons:{" "}
                <strong className="text-[#f3eee4]">IT IS MINECRAFT.</strong>
              </p>
              <p className="mt-3 leading-relaxed text-[#cfc6b8]">
                So making a real physics engine in C++ feels like a cool
                challenge
              </p>
            </section>
          </div>

          {/* chapter 4 — screenshots */}
          <div className="relative mt-14">
            <PathNode label="chapter four — where it stands" />
            <section className="mt-4">
              <div className="flex flex-col gap-10">
                {screenshots.map((shot) => (
                  <figure
                    key={shot.src}
                    className="overflow-hidden rounded-2xl border border-white/10 bg-[#241f30] transition-transform hover:-rotate-1 hover:scale-[1.01]"
                  >
                    <Image
                      src={shot.src}
                      alt={shot.alt}
                      width={1280}
                      height={720}
                      className="w-full object-contain"
                    />
                    <figcaption className="border-t border-white/10 p-6">
                      <h3 className="mb-1 text-lg font-semibold text-[#f3eee4]">
                        {shot.title}
                      </h3>
                      <p className="text-sm leading-relaxed text-[#b8ae9d]">
                        {shot.caption}
                      </p>
                    </figcaption>
                  </figure>
                ))}
              </div>
            </section>
          </div>

          {/* the end of the path */}
          <div className="relative mt-14">
            <PathNode label="the end of the path — for now" />
            <section className="mt-4 rounded-2xl border border-[#f5c66b]/40 bg-gradient-to-b from-[#f5c66b]/10 to-[#241f30] p-8 text-center">
              <h2 className="text-2xl font-semibold text-[#f5c66b]">
                FINAL GOAL
              </h2>
              <p className="mx-auto mt-3 max-w-xl leading-relaxed text-[#cfc6b8]">
                Make a custom physics engine in which I can create a
                human-like character and teach it to do a backflip —{" "}
                <strong className="text-[#f3eee4]">
                  then I can finally watch that YouTube video
                </strong>{" "}
                ;DDDD
              </p>
              <a
                href="https://github.com/Druidman/PhysicsEngine"
                target="_blank"
                rel="noopener noreferrer"
                className="mt-5 inline-block rounded-full bg-[#f5c66b]/20 px-6 py-2.5 font-medium text-[#f5c66b] transition-colors hover:bg-[#f5c66b]/30"
              >
                Check it out on Github
              </a>
              <a
                href="https://github.com/Druidman/PhysicsEngine/releases/tag/v0.0"
                target="_blank"
                rel="noopener noreferrer"
                className="mt-3 ml-3 inline-block rounded-full border border-[#a8d5c2]/40 px-6 py-2.5 font-medium text-[#a8d5c2] transition-colors hover:bg-[#a8d5c2]/10"
              >
                Download for Linux
              </a>
            </section>
          </div>
        </div>

        <footer className="border-t border-white/10 pt-6 text-center text-sm text-[#8f86a8]">
          Made with love, curiosity, and one very spinny cube. 🧊💫
        </footer>
      </main>
    </div>
  );
}
