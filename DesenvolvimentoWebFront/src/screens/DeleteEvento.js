import { useState } from 'react'; 
import axios from "axios";
/*
{
  name:
  price:
  type:
  brand:
}
*/
function DeleteItems(props){

    const [id, setId] = useState("")
    const [name, setName] = useState("")
    const [description, setDescription] = useState("")
    const [date, setDate] = useState("")
    const [time, setTime] = useState("")
    const [classification, setClassification] = useState("")
    const [capacity, setCapacity] = useState("")
    const [organizador, setOrganizador] = useState("")

    const deleteItemsButtonPressed = async () => {

        var token = localStorage.getItem("token");
        console.log(token);
        const config = { //salvar esse token dentro dessa config
          headers: { Authorization: `Bearer ${token}` }
        };

        try {
          // const response = "TESTE";
          const response = await axios.delete(`http://localhost:8080/evento/${id}`, 
            // request_body,
            config
          );
          console.log("Sucesso ao excluir evento! ", response.data);
        } catch (error) {
          console.error("Erro ao tentar excluir evento", error);
        }
    }

  return (
    <div> 
      <div className='container'>
        <div className='row'>
          <h2>Deletar Evento</h2>
        </div>
        <div className='row'>
          <label>Id do Evento: </label>
          <input id="name-field" className='form-control' type="text" value={id} onChange={ (e) => setId(e.target.value) }/>
        </div>
        <div className='row'>
          <button type="button" className='btn btn-dark mt-3' onClick={deleteItemsButtonPressed}>Ver</button>
        </div>
      </div>
    </div>
  )
}

export default DeleteItems;