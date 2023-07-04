package TJV.olsheden_semestral.controller;

import TJV.olsheden_semestral.Exception.FieldsCannotBeEmpty;
import TJV.olsheden_semestral.Exception.InvalidStateException;
import TJV.olsheden_semestral.Exception.NotFoundException;
import TJV.olsheden_semestral.domain.Client;
import TJV.olsheden_semestral.dtos.ClientDto;
import TJV.olsheden_semestral.service.ClientService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import java.util.Collection;
import java.util.stream.StreamSupport;
import java.util.function.Function;

@RestController
@RequestMapping("/clients")
public class ClientController {

    @Autowired
    protected ClientService clientService;
    @Autowired
    protected OrderController orderController;

    @Autowired
    protected Function<Client, ClientDto> clientCovertToDto;

    @Autowired
    protected Function<ClientDto, Client> clientCovertToEntity;

    public ClientController(ClientService clientService, OrderController orderController, Function<Client, ClientDto> clientCovertToDto, Function<ClientDto, Client> clientCovertToEntity) {
        this.clientService = clientService;
        this.orderController = orderController;
        this.clientCovertToDto = clientCovertToDto;
        this.clientCovertToEntity = clientCovertToEntity;
    }

    @PostMapping
    public ClientDto createClient(@RequestBody ClientDto clientDto) throws FieldsCannotBeEmpty, InvalidStateException, NotFoundException {
        return clientCovertToDto.apply(clientService.create(clientCovertToEntity.apply(clientDto)));
    }


    @GetMapping("/{id}")
    public ResponseEntity<ClientDto> readOne(@PathVariable Long id) throws NotFoundException {
        var result = clientService.readById(id);
        if(result.isPresent()){
            return ResponseEntity.ok(clientCovertToDto.apply(result.get()));
        }
        else{
            return ResponseEntity.notFound().build();
        }
    }


    @GetMapping("")
    public Collection<ClientDto> readAll(){
        return StreamSupport.stream(clientService.readAll().spliterator(), false).map(clientCovertToDto).toList();
    }

    @PutMapping("/{id}")
    public void updateClient(@RequestBody ClientDto clientDto, @PathVariable Long id) throws NotFoundException, FieldsCannotBeEmpty {
        clientService.update(clientCovertToEntity.apply(clientDto));
    }

    @DeleteMapping("/{id}")
    public void deleteClient(@PathVariable Long id) throws NotFoundException {
        clientService.deleteById(id);
    }

}
