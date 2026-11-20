import Image from "next/image";

const screenshots = [
  {
    src: "/engineshowcase.png",
    title: "Chapter: the engine",
    caption:
      "The engine's current state — very early development. Right now only object rendering works... and we managed to make a spinning cube!! 🎉",
    alt: "Current state of the physics engine",
  },
  {
    src: "/neuralnetworkshowcase.png",
    title: "Chapter: the network",
    caption:
      "The network's current state — learning from scratch, starting with handwritten digits before it ever touches a backflip.",
    alt: "Current state of the neural network",
  },
];

export default function Home() {
  return (
    <div className="flex min-h-full flex-col bg-[#1c1a24] text-[#f3eee4]">
      {/* cozy banner */}
      <div className="border-b border-white/10 bg-[#2a2536] px-4 py-3 text-center text-sm text-[#d9cfb8]">
        ✨ This is a{" "}
        <span className="font-semibold text-[#f5c66b]">vibecoded</span> website
        — just a small showcase of how the project works right now.{" "}
        <span className="font-semibold text-[#f5c66b]">
          It is NOT finished!
        </span>{" "}
        ✨
      </div>

      <main className="mx-auto flex w-full max-w-3xl flex-1 flex-col gap-16 px-6 py-16">
        {/* hero */}
        <header className="text-center">
          <p className="mb-2 text-sm uppercase tracking-[0.3em] text-[#8f86a8]">
            a cozy story about physics and backflips
          </p>
          <h1 className="text-4xl font-bold tracking-tight text-[#f5c66b] sm:text-5xl">
            PhysicsSim
          </h1>
          <p className="mx-auto mt-4 max-w-xl text-lg leading-relaxed text-[#cfc6b8]">
            The name says &quot;physics engine&quot;, but the real mission?{" "}
            <strong className="text-[#f5c66b]">
              Trying to teach AI how to do a backflip.
            </strong>{" "}
            This is the story of how it&apos;s going so far.
          </p>
        </header>

        {/* story: where the idea came from */}
        <section className="rounded-2xl border border-white/10 bg-[#241f30] p-8">
          <h2 className="text-2xl font-semibold text-[#f5c66b]">
            🌱 Where does this idea come from?
          </h2>
          <p className="mt-3 leading-relaxed text-[#cfc6b8]">
            One day, a YouTube thumbnail appeared on my main page about making
            this exact thing — an AI learning to backflip. I decided{" "}
            <strong className="text-[#f3eee4]">
              not to watch it until I build something like this myself.
            </strong>{" "}
            Why? Well, just bc. Also I&apos;ve never made a physics engine
            before. I always kind of ran away from the idea of properly
            calculating collisions, forces, etc. — it just felt hard for me.
          </p>
          <p className="mt-3 leading-relaxed text-[#cfc6b8]">
            And I&apos;d never made a neural network before either. Even
            better: I decided to do it{" "}
            <strong className="text-[#f3eee4]">from scratch</strong>, so I can
            understand the underlying math instead of hiding behind a library.
          </p>
          <p className="mt-3 leading-relaxed text-[#cfc6b8]">
            So the whole project stands on two main pillars:
          </p>
          <div className="mt-4 grid gap-3 sm:grid-cols-2">
            <div className="rounded-xl bg-[#2e2940] p-4 text-center">
              <span className="text-2xl">🧱</span>
              <p className="mt-1 font-semibold text-[#f3eee4]">The engine</p>
              <p className="text-sm text-[#b8ae9d]">
                physics, collisions, forces — the hard stuff
              </p>
            </div>
            <div className="rounded-xl bg-[#2e2940] p-4 text-center">
              <span className="text-2xl">🧠</span>
              <p className="mt-1 font-semibold text-[#f3eee4]">
                The neural network
              </p>
              <p className="text-sm text-[#b8ae9d]">
                trained to make a body inside the engine backflip
              </p>
            </div>
          </div>
        </section>

        {/* story: neural network */}
        <section className="rounded-2xl border border-white/10 bg-[#241f30] p-8">
          <h2 className="text-2xl font-semibold text-[#f5c66b]">
            🧠 About the neural network
          </h2>
          <p className="mt-3 leading-relaxed text-[#cfc6b8]">
            I&apos;m just learning how to make neural networks from scratch, so
            I started at the classical AI entry point:{" "}
            <strong className="text-[#f3eee4]">the MNIST dataset</strong>{" "}
            (handwritten digits).
          </p>
          <p className="mt-3 leading-relaxed text-[#cfc6b8]">
            So far I&apos;ve managed to implement{" "}
            <strong className="text-[#f3eee4]">working calculus math</strong>{" "}
            in Python and a proper NN structure (it is{" "}
            <em>nowhere near</em> optimized xD). Once MNIST works properly{" "}
            <em>and</em> fast, the network graduates and moves onto my
            in-engine character. That&apos;s the plan.
          </p>
        </section>

        {/* story: engine */}
        <section className="rounded-2xl border border-white/10 bg-[#241f30] p-8">
          <h2 className="text-2xl font-semibold text-[#f5c66b]">
            🧱 About the engine
          </h2>
          <p className="mt-3 leading-relaxed text-[#cfc6b8]">
            I had previous experience with C++ and OpenGL — I made a{" "}
            <strong className="text-[#f3eee4]">Minecraft clone</strong> in
            OpenGL and C++ before. But it didn&apos;t include{" "}
            <em>any</em> physics, for obvious reasons:{" "}
            <strong className="text-[#f3eee4]">IT IS MINECRAFT.</strong>
          </p>
          <p className="mt-3 leading-relaxed text-[#cfc6b8]">
            So making a real physics engine in C++ feels like a cool challenge
            — the exact kind of thing I used to run away from, now something I
            actually want to overcome.
          </p>
        </section>

        {/* screenshots */}
        <section>
          <h2 className="mb-8 text-center text-2xl font-semibold text-[#f5c66b]">
            📸 Screenshots — current state
          </h2>
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

        {/* final goal */}
        <section className="rounded-2xl border border-[#f5c66b]/40 bg-gradient-to-b from-[#f5c66b]/10 to-[#241f30] p-8 text-center">
          <h2 className="text-2xl font-semibold text-[#f5c66b]">
            🏁 FINAL GOAL
          </h2>
          <p className="mx-auto mt-3 max-w-xl leading-relaxed text-[#cfc6b8]">
            Make a custom physics engine in which I can create a human-like
            character and teach it to do a backflip —{" "}
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
            🐙 Want to see how it actually looks right now? — github.com/Druidman/PhysicsEngine
          </a>
        </section>

        <footer className="border-t border-white/10 pt-6 text-center text-sm text-[#8f86a8]">
          Made with love, curiosity, and one very spinny cube. 🧊💫
        </footer>
      </main>
    </div>
  );
}
