// Require the necessary discord.js classes
const Discord = require('discord.js');
const { token } = require('./config.json');

// Create a new client instance
const client = new Discord.Client({
        intents: [
        "GUILDS",
        "GUILD_MESSAGES"
      ]
    });

// When the client is ready, run this code (only once)
client.once("ready", () => {
	console.log('Ready!');
});

client.on("messageCreate", (message) => {
    const args = message.content;

    if(args.startsWith("!")) {
      switch (args) {
        case "!bruh" :
          message.reply("19 dollar fortnite card");
          break;
        case "!u smell" :
          message.reply("no u");
          break;
        default :
          break;
      }
    }
    // else {
    //   const gifSetter = args.split(" ");
    //   const linktest = gifSetter.toString();
    //   if(gifSetter.length == 1 && linktest.substring(0, 6) != "https:") {
    //     message.reply("https://media.tenor.com/DXeA2HkpYcsAAAAC/anime-kurisu.gif")
    //   }
    // }

});

// Login to Discord with your client's token
client.login(token);
