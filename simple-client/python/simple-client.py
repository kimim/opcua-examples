from asyncua import Client

async def main():
    async with Client(url='opc.tcp://localhost:4840') as client:
        # Do something with client
        node = client.get_node('i=2258')
        value = await node.read_value()
        print(f'Server Time: {value}')


if __name__ == "__main__":
    import asyncio
    asyncio.run(main())
