import { useState } from 'react'; 
import axios from "axios";
/*
{
  tipo:
  qnt disponivel:
  preco:
  qrcode:
  setor:
}
*/
function AddItems(props){

    const [tipo, setTipo] = useState("")
    const [qntDisponivel, setQntDisponivel] = useState("")
    const [preco, setPreco] = useState("")
    const [setor, setSetor] = useState("")

    const addItemsButtonPressed = async () => {
      // props.addItems({
      //       "name": name,
      //       "description": description,
      //       "date" : date,
      //       "time" : time,
      //       "type": type,
      //       "classification": classification,
      //       "capacity": capacity
      //   })

      // const request_body = {
      //   "nome":"TESTE",
      //   "descricao":"TESTE1",
      //   "data":"2024-10-01",
      //   "horario_inicio":"22:08:28",
      //   "horario_fim": "22:08:28",
      //   "classificacao_indicativa":"1",
      //   "lotacao_maxima":200,
      //   //"endereco":
      //   "organizador":1,
      // }
      // var token = localStorage.getItem("token");
      // console.log(token);
      // const config = {
      //   headers: { Authorization: `Bearer ${token}` }
      // };

      // try {
      //   // const response = "TESTE";
      //   const response = await axios.post("http://localhost:8080/evento/", 
      //     request_body,
      //     config
      //   );
      //   console.log("Sucesso ao cadastrar Evento: ", response.data);
        
      // } catch (error) {
      //   console.error("Error signing up:", error);
      // }

    setTipo("")
    setQntDisponivel("")
    setPreco("")
    setTimeout("")
    setSetor("")

    }

  return (
    <div> 
      <div className='container'>
        <div className='row'>
          <h2>Adicionar Ingresso</h2>
        </div>
        <div className='row'>
          <label>Tipo do Ingresso: </label>
          <input id="name-field" className='form-control' type="text" value={tipo} onChange={ (e) => setTipo(e.target.value) }/>
        </div>          
        <div className='row'>
          <label>Quantidade Disponivel: </label>
          <input id="description-field" className='form-control' type="text" value={qntDisponivel} onChange={ (e) => setQntDisponivel(e.target.value) }/>
        </div>  
        <div className='row'>
          <label>Preço: </label>
          <input id="date-field" className='form-control' type="text" value={preco} onChange={ (e) => setPreco(e.target.value)}/>
        </div>       
        <div className='row'>
          <label>Setor: </label>
          <input id="type-field" className='form-control' type="text" value={setor} onChange={ (e) => setSetor(e.target.value) }/>
        </div>  
        <div className='row'>
          <button type="button" className='btn btn-dark mt-3' onClick={addItemsButtonPressed}>Adicionar</button>
        </div>
      </div>
    </div>
  )
}

export default AddItems;